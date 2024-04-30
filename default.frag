#version 330 core

out vec4 FragColor;

in vec3 FragPos; // Input position from vertex shader changed
in vec3 Normal; // Input normal from vertex shader changed



in vec3 thisColor;
in vec2 texCoord;

uniform sampler2D tex0;

uniform vec3 objectColor; // Color of the object changed

void main()
{
   FragColor = texture(tex0, texCoord);
   
    // Ambient light color changed
    vec3 ambientColor = vec3(0.1, 0.1, 0.1); // Dark ambient light changed

    // Calculate ambient lighting
    vec3 ambient = ambientColor * texture(tex0, texCoord).rgb; //changed

    // Simulate self-illumination by directly applying texture color
    // Final color is the sum of ambient light and texture color changed
    FragColor = vec4(ambient, 1.0); //changed

    // Set the object color directly without relying on texture
    FragColor = vec4(objectColor, 1.0); //changed
    
   /*vec4 texColor = texture(tex0, texCoord); // Use the passed color
   //FragColor = vec4(texColor.rgb * thisColor, texColor.a);*/

}