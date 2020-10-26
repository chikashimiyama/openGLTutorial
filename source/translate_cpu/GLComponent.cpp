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
    shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);

    if (!shader_->addVertexShader (BinaryData::minimal_vert)
        && shader_->addFragmentShader (BinaryData::minimal_frag)
        && shader_->link())
    {
        throw std::runtime_error("Shader compilation error");
    }

    // vec4 because mat4 requires vec4 . xyzw where w is scale factor
    vertices_ = std::array<glm::vec4, 3>{{{0.0f, 0.5f, 0.0f, 1.0f},{0.5f, -0.5f, 0.0f, 1.0f},{-0.5f, -0.5f, 0.0f, 1.0f}}};


    const auto modelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.25f, 0.f, 0.f)); // move to right

    // this is very costly operation if the number of vertices is very high.
    std::transform(vertices_.begin(), vertices_.end(), vertices_.begin(), [&modelMatrix](const glm::vec4& vertex){
        return modelMatrix * vertex;
    });

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
    const auto desktopScale = (float) openGLContext.getRenderingScale(); // 2.0 when retina
    glClearColor(0.f, 0.f, 0.3f, 1.f);
    glViewport(0, 0, getWidth() * desktopScale , getHeight() * desktopScale);

    glClear(GL_COLOR_BUFFER_BIT);

    shader_->use();

    glEnableVertexAttribArray (0); // define position vbo as the 0th attribute
    glBindBuffer (GL_ARRAY_BUFFER, positionVboId_);
    glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, 3); // draw actual GLComponent

    glDisableVertexAttribArray(0);
}

void GLComponent::paint(juce::Graphics& g)
{
    auto str = juce::String();
    for(auto& vertex : vertices_)
        str += juce::String("{") + juce::String(vertex.x, 2) + " " + juce::String(vertex.y, 2) + " " + juce::String(vertex.z, 2) + "}\n";

    g.setColour(juce::Colour(255, 255, 255));
    g.drawMultiLineText(str, 10, 50, 600);
}
