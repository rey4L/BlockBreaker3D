// Inside your fragment shader
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  
    float shininess;
};

uniform Material material;

void main() {
    // Ambient lighting
    vec3 ambient = material.ambient * light.ambient;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.diffuse * (diff * light.diffuse);

    // Specular lighting
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * (spec * light.specular);  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
