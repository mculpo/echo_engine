#version 330 core

out vec4 color;

in vec2 texCoord0;


// texture samplers
uniform sampler2D texture0;

void main()
{
	color = texture2D(texture0, texCoord0);
}