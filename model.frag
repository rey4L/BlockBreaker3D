#version 330 core
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D diffuseMap;

void main()
{    
    FragColor = texture(diffuseMap, TexCoords);
}