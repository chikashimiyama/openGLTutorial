#version 120

varying vec2 fTexCoord;
uniform sampler2D tex; // point actual texture on VRAM

void main()
{
    vec4 color = texture2D(tex, fTexCoord);

    for(int i = 1; i < 5; i++ )
    {
        float offset = i * 0.01;
        color += texture2D(tex, fTexCoord + vec2(offset, 0.0));
        color += texture2D(tex, fTexCoord + vec2(offset, -offset));
        color += texture2D(tex, fTexCoord + vec2(0.0, -offset));
        color += texture2D(tex, fTexCoord + vec2(-offset, -offset));
        color += texture2D(tex, fTexCoord + vec2(-offset, 0.00));
        color += texture2D(tex, fTexCoord + vec2(-offset, offset));
        color += texture2D(tex, fTexCoord + vec2(0.0, offset));
        color += texture2D(tex, fTexCoord + vec2(offset, 0.01));
    }

    gl_FragColor = color / 37.0;
}