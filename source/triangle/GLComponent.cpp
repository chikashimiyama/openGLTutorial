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
    // define the vertices of the triangle
    vertices_ = std::array<glm::vec4, 3>{{{0.0f, 0.5f, 0.0f, 1.0f},{0.5f, -0.5f, 0.0f, 1.0f},{-0.5f, -0.5f, 0.0f, 1.0f}}};

    // create a shader
    shader_ = std::make_unique<OpenGLShaderProgram>(openGLContext);

    // compile and link program
    if (!(shader_->addVertexShader (BinaryData::minimal_vert)
        && shader_->addFragmentShader (BinaryData::minimal_frag)
        && shader_->link()))
    {
        throw std::runtime_error("Shader compilation error");
    }

    positionAttribute_ = std::make_unique<OpenGLShaderProgram::Attribute>(*shader_, "position"); // just holds attribute index

    // generate VBO and copy data to it
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
    glViewport(0, 0, getWidth() * desktopScale , getHeight() * desktopScale); // define how big is the convas of GL

    glClearColor(0.f, 0.f, 0.3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT); // clean window

    shader_->use();

    glBindBuffer (GL_ARRAY_BUFFER, positionVboId_); // specify the vbo (a certain location of VRAM)

    glEnableVertexAttribArray (positionAttribute_->attributeID); // enable position attribute
    glVertexAttribPointer (positionAttribute_->attributeID, 4, GL_FLOAT, GL_FALSE, 0, NULL); // gives the hint of data structure
    glDrawArrays(GL_TRIANGLES, 0, 3); // this command let GL draw actual triangle
    glDisableVertexAttribArray(positionAttribute_->attributeID); // disable position attribute
}

void GLComponent::paint(juce::Graphics& g)
{
    auto str = juce::String();
    for(auto& vertex : vertices_)
        str += juce::String("{") + juce::String(vertex.x, 2) + " " + juce::String(vertex.y, 2) + " " + juce::String(vertex.z, 2) + "}\n";

    g.setColour(juce::Colour(255, 255, 255));
    g.drawMultiLineText(str, 10, 50, 600);
}
