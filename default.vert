#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Input for color
layout (location = 2) in vec2 aTex;

out vec3 thisColor; // Output to fragment shader
out vec2 texCoord;
uniform float scale; // Uniform to scale our axes

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(aPos * scale, 1.0);
	thisColor = aColor * scale;
	texCoord = aTex;
}