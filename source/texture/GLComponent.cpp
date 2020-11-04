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
    texCoords_ = std::array<glm::vec2, 3>{{{0.5f, 1.0f},{1.0f, 0.0f},{0.0f, 0.0f}}};

    texture_.loadImage(juce::ImageCache::getFromMemory(BinaryData::texture_png, BinaryData::texture_pngSize));

    shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);

    if (!(shader_->addVertexShader (BinaryData::texture_vert)
          && shader_->addFragmentShader (BinaryData::texture_frag)
          && shader_->link()))
    {
        throw std::runtime_error("Shader compilation error");
    }

    shader_->use();

    positionAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "position");
    texCoordAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "texCoord");

    glGenBuffers(1, &positionVboId_);
    glBindBuffer(GL_ARRAY_BUFFER, positionVboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &texCoordVboId_);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVboId_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords_), texCoords_.data(), GL_STATIC_DRAW);

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

    glBindBuffer (GL_ARRAY_BUFFER, texCoordVboId_);
    glEnableVertexAttribArray (texCoordAttribute_->attributeID);
    glVertexAttribPointer (texCoordAttribute_->attributeID, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    texture_.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    texture_.unbind();

    glDisableVertexAttribArray(positionAttribute_->attributeID);
    glDisableVertexAttribArray(texCoordAttribute_->attributeID);
}

void GLComponent::paint(juce::Graphics& g)
{

}
