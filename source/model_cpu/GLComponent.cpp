#include "GLComponent.h"

#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include "BinaryData.h"

using namespace juce;

GLComponent::GLComponent()
{
    setSize (800, 600);
}

GLComponent::~GLComponent()
{
    shutdownOpenGL();
}

void GLComponent::initialise()
{
    vertices_ = std::array<glm::vec4, 3>{{{0.0f, 0.5f, 0.0f, 1.0f},{0.5f, -0.5f, 0.0f, 1.0f},{-0.5f, -0.5f, 0.0f, 1.0f}}};
    shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);

    if (!(shader_->addVertexShader (BinaryData::minimal_vert)
          && shader_->addFragmentShader (BinaryData::minimal_frag)
          && shader_->link()))
    {
        throw std::runtime_error("Shader compilation error");
    }

    positionAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "position"); // just holds attribute index

    /**** modifying vertices using matrix ****/
    auto modelMatrix = glm::scale(glm::mat4(1.0), glm::vec3(0.5f, 0.5f, 0.5f)); // scale by 0.5
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.25f, 0.f, 0.f)); // move to the right
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0.f, 0.f, 1.f)); // 180 degrees rotation

    std::transform(vertices_.begin(), vertices_.end(), vertices_.begin(), [&modelMatrix](const glm::vec4& vertex){
        return modelMatrix * vertex;
    });
    /**** modifying vertices using matrix ****/

    glGenBuffers(1, &positionVboId_);
    glBindBuffer(GL_ARRAY_BUFFER, positionVboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLComponent::shutdown()
{
}

void GLComponent::render()
{
    const auto desktopScale = (float) openGLContext.getRenderingScale();
    glViewport(0, 0, getWidth() * desktopScale , getHeight() * desktopScale);

    glClearColor(0.f, 0.f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_->use();

    glBindBuffer (GL_ARRAY_BUFFER, positionVboId_);

    glEnableVertexAttribArray (positionAttribute_->attributeID);
    glVertexAttribPointer (positionAttribute_->attributeID, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(positionAttribute_->attributeID);
}

void GLComponent::paint(juce::Graphics& g)
{
    auto str = juce::String();
    for(auto& vertex : vertices_)
        str += juce::String("{") + juce::String(vertex.x, 2) + " " + juce::String(vertex.y, 2) + " " + juce::String(vertex.z, 2) + "}\n";

    g.setColour(juce::Colour(255, 255, 255));
    g.drawMultiLineText(str, 10, 50, 600);
}
