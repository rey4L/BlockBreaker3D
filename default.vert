#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; // Input for color
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal; // Input for normal changed 

out vec3 FragPos; // Output position for fragment shader changed
out vec3 Normal; // Output normal for fragment shader changed


out vec3 thisColor; // Output to fragment shader
out vec2 texCoord;
uniform float scale; // Uniform to scale our axes

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(aPos * scale, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0)); // Transform position to world space changed
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space changed
	thisColor = aColor * scale;
	texCoord = aTex;
}