#version 330 core

out vec4 color;

in vec3 fragColor;
in vec2 texCoord;


// texture samplers
uniform sampler2D diffuse;

void main()
{
	vec4 texColor = texture(diffuse, texCoord);
	if(texColor.a < 0.05)
        discard;
    color = texColor;
}