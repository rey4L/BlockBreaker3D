#version 330 core

in vec2 TexCoords;
in vec3 FragPos; // Position of the fragment in world space
in vec3 Normal;  // Normal vector of the fragment

out vec4 FragColor;

uniform sampler2D diffuseMap;
uniform vec3 lightPos;    // Position of the light source
uniform vec3 lightColor;  // Color of the light source
uniform vec3 viewPos;     // Position of the camera/viewer


// Lighting parameters
uniform vec3 ambientColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;

void main()
{    
    // Ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // Combine ambient and diffuse lighting
    vec3 result = (ambient + diffuse + specular) * texture(diffuseMap, TexCoords).rgb;

    FragColor = vec4(result, 1.0);

    FragColor = texture(diffuseMap, TexCoords);
}