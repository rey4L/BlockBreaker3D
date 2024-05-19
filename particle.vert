#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aVel;
layout (location = 2) in float aLifespan;
layout (location = 3) in float aSize;
layout (location = 4) in float aFade;

uniform mat4 view;
uniform mat4 projection;

out float VFade;

void main() {
    gl_Position = projection * view * vec4(aPos, 1.0);
    gl_PointSize = aSize;
    VFade = aFade;
}