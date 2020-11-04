#pragma once
#include <array>
#include <glm/glm.hpp>
#include <juce_opengl/juce_opengl.h>
#include <juce_gui_basics/juce_gui_basics.h>

class GLComponent : public juce::OpenGLAppComponent
{
public:
    GLComponent();

    ~GLComponent();

    void initialise() override;

    void shutdown() override;

    void render() override;

    void paint(juce::Graphics& g) override;

private:
    std::array<glm::vec4, 3> vertices_;
    std::array<glm::vec2, 3> texCoords_;

    std::unique_ptr<juce::OpenGLShaderProgram> shader_;
    std::unique_ptr<juce::OpenGLShaderProgram::Attribute> positionAttribute_;
    std::unique_ptr<juce::OpenGLShaderProgram::Attribute> texCoordAttribute_;

    GLuint positionVboId_ {INT_MAX } ;
    GLuint texCoordVboId_ {INT_MAX } ;

    juce::OpenGLTexture texture_;
};