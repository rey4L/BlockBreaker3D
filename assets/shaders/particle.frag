#version 330 core
out vec4 FragColor;

uniform vec4 particleColor;
in float VFade;

void main() {

    float brightness = dot(particleColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    float bloomThreshold = 0.7; // Adjust the threshold as needed
    
    if (brightness > bloomThreshold) {
        vec3 bloomColor = particleColor.rgb * (brightness - bloomThreshold) * 0.8;
        FragColor = vec4(bloomColor, particleColor.a * VFade);
    } else {
        FragColor = vec4(particleColor.rgb, particleColor.a * VFade);
    }
    
    FragColor.a *= VFade;
}
