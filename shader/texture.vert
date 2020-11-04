#version 120

attribute vec4 position;
attribute vec2 texCoord;

varying vec2 fTexCoord;

void main(){
    fTexCoord = texCoord;
    gl_Position = position;
}
