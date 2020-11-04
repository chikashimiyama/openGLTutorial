#version 120

varying vec2 fTexCoord;
uniform sampler2D tex; // point actual texture on VRAM

void main()
{
    gl_FragColor = texture2D(tex, fTexCoord);
}