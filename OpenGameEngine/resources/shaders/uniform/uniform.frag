#version 330 core

out vec4 color;

in vec3 fragColor;
in vec2 texCoord;

uniform sampler2D normal;

void main()
{
	vec4 texColor = texture(normal, texCoord);
	if(texColor.a < 0.05)
        discard;
    color = texColor;
}