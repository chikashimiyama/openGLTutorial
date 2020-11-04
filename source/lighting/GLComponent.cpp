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
    normals_ = std::array<glm::vec4, 3>{{{0.0f, 1.0f, 0.0f, 1.0f},{1.0f, 0.0f, 0.0f, 1.0f},{-1.0f, 0.0f, 0.0f, 1.0f}}}; // the length of normals should be 1.0f

    shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);

    if (!(shader_->addVertexShader (BinaryData::normal_vert)
          && shader_->addFragmentShader (BinaryData::normal_frag)
          && shader_->link()))
    {
        throw std::runtime_error("Shader compilation error");
    }

    positionAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "position"); // just holds attribute index
    normalAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "normal"); // just holds attribute index

    glGenBuffers(1, &positionVboId_);
    glBindBuffer(GL_ARRAY_BUFFER, positionVboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &normalVboId_);
    glBindBuffer(GL_ARRAY_BUFFER, normalVboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normals_), normals_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GLComponent::shutdown()
{
}

void GLComponent::render()
{
    const auto desktopScale = (float) openGLContext.getRenderingScale(); // 2.0 when retina
    glViewport(0, 0, getWidth() * desktopScale , getHeight() * desktopScale); // define how big is the convas of GL

    glClearColor(0.f, 0.f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT); // clean window

    shader_->use();
    shader_->setUniform("lightPosition", 1.0f, 0.0f, 0.0f, 1.0f);

    glBindBuffer (GL_ARRAY_BUFFER, positionVboId_);
    glEnableVertexAttribArray (positionAttribute_->attributeID);
    glVertexAttribPointer (positionAttribute_->attributeID, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer (GL_ARRAY_BUFFER, normalVboId_);
    glEnableVertexAttribArray (normalAttribute_->attributeID);
    glVertexAttribPointer (normalAttribute_->attributeID, 4, GL_FLOAT, GL_FALSE, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(positionAttribute_->attributeID);
    glDisableVertexAttribArray(normalAttribute_->attributeID);

}

void GLComponent::paint(juce::Graphics& g)
{

}
