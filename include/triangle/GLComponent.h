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
    std::array<glm::vec3, 3> vertices_;
    std::unique_ptr<juce::OpenGLShaderProgram> shader_;
    GLuint positionVboId_ {INT_MAX } ;
};