#version 330 core
out vec4 FragColor;
in vec3 thisColor;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, texCoord);

   /*vec4 texColor = texture(tex0, texCoord); // Use the passed color
   //FragColor = vec4(texColor.rgb * thisColor, texColor.a);*/
}