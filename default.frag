#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

// PBR uniforms
uniform vec3 objectColor;
uniform float metallic;
uniform float roughness;
uniform float ao;

// Light properties
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

// Tone mapping exposure
uniform float exposure;

const float PI = 3.14159265359;

// Fresnel-Schlick approximation
vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

// Normal Distribution Function using GGX/Trowbridge-Reitz
float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    
    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    
    return num / denom;
}

// Geometry function using Smith's Schlick-GGX
float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;
    
    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    
    return ggx1 * ggx2;
}

void main() {
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    vec3 L = normalize(lightPos - FragPos);
    vec3 H = normalize(V + L);
    
    // Calculate Fresnel factor
    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, objectColor, metallic);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
    
    // Calculate normal distribution
    float NDF = DistributionGGX(N, H, roughness);
    
    // Calculate geometry factor
    float G = GeometrySmith(N, V, L, roughness);
    
    // Calculate specular term
    vec3 numerator = NDF * G * F;
    float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; 
    vec3 specular = numerator / denominator;
    
    // Calculate diffuse term
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;
    
    float NdotL = max(dot(N, L), 0.0);
    vec3 Lo = (kD * objectColor / PI + specular) * lightColor * NdotL;
    
    // Add ambient term
    vec3 ambient = vec3(0.03) * objectColor * ao;
    vec3 color = ambient + Lo;
    
    // Gamma correction
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 4.5));
    
    FragColor = vec4(color, 1.0);
}
