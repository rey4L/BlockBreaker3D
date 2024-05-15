#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
//in vec2 texCoord;

//uniform sampler2D tex0;
uniform vec3 objectColor;

// Light properties
uniform vec3 lightPos;    // Position of the light source
uniform vec3 lightColor;  // Color of the light source
uniform vec3 viewPos;     // Position of the camera (for specular lighting)

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // Ambient component
    vec3 ambientColor = vec3(1.0, 1.0, 1.0);
    vec3 ambient = ambientColor;
    
    // Diffuse component
    float diff = max(dot(norm, lightDir), 0.5);
    vec3 diffuse = diff * lightColor;
    
    // Specular component
    float specularStrength = 1.25;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 1.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
    
    // Combine results
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}