#include "GLComponent.h"

#include <array>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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

    if (!(shader_->addVertexShader (BinaryData::mvp_vert)
          && shader_->addFragmentShader (BinaryData::minimal_frag)
          && shader_->link()))
    {
        throw std::runtime_error("Shader compilation error");
    }

    positionAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "position"); // just holds attribute index

    auto viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.f, 1.5f), glm::vec3(0.0f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));

    const auto aspectRatio = static_cast<float>(getWidth())/static_cast<float>(getHeight());
    auto projectionMatrix = glm::perspective<float>(glm::radians(70.0f), aspectRatio, 0.1f, 100.f);

    /**** passing matrices to VRAM ****/
    shader_->use();
    shader_->setUniformMat4("viewMatrix", glm::value_ptr(viewMatrix), 1, GL_FALSE);
    shader_->setUniformMat4("projectionMatrix", glm::value_ptr(projectionMatrix), 1, GL_FALSE);


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

    glEnable(GL_CULL_FACE);
    shader_->use();
    auto modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degree_), glm::vec3(0.f, 1.f, 0.f));
    shader_->setUniformMat4("modelMatrix", glm::value_ptr(modelMatrix), 1, GL_FALSE);

    glBindBuffer (GL_ARRAY_BUFFER, positionVboId_);

    glEnableVertexAttribArray (positionAttribute_->attributeID);
    glVertexAttribPointer (positionAttribute_->attributeID, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(positionAttribute_->attributeID);
    glDisable(GL_CULL_FACE);

    degree_ += 5.0f;
}

void GLComponent::paint(juce::Graphics& g)
{

}
