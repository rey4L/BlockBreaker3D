#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos; // Position of the fragment in world space
out vec3 Normal;  // Normal vector of the fragment

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    FragPos = vec3(model * vec4(aPos, 1.0));  // Calculate position in world space
    Normal = mat3(transpose(inverse(model))) * aNormal; // Transform normal to world space
    TexCoords = aTexCoords;    
}