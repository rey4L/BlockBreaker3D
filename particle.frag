#version 330 core
out vec4 FragColor;

uniform vec4 particleColor;
in float VFade;

void main() {
    FragColor = particleColor * VFade; // Orange color for sparks
}
