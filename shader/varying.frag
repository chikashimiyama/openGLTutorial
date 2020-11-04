#version 120

varying float absX;

void main() {
    gl_FragColor = vec4(absX, 1.0, 1.0 - absX, 1.0);
}
