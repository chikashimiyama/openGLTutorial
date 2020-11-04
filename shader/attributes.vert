#version 120

attribute vec4 position; // attribute 0
attribute vec4 color; // attribute 1

varying vec4 fColor;

void main() {
    fColor = color;
    gl_Position = position;
}
