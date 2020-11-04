#version 120

attribute vec4 position;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
varying float absX; // send absolute distance from the center to the fragment shader

void main() {

    vec4 worldSpace = modelMatrix * position;
    absX = clamp(abs(worldSpace.x), 0.0, 1.0);

    gl_Position = projectionMatrix * viewMatrix * worldSpace;
}
