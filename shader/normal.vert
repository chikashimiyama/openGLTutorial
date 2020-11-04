#version 120

attribute vec4 position;
attribute vec4 normal;

uniform vec4 lightPosition;

varying float lightIntensity;

void main(){
    lightIntensity = dot (lightPosition, normal) * 0.5;
    gl_Position = position;
}
