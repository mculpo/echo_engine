#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

layout (location = 3) in mat4 aInstanceMatrix;

out vec2 texCoord;
out vec3 color;

layout(std140) uniform Matrices {
    mat4 projection; 
    mat4 view;  
};

void main () 
{
	gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f);
	color = aColor;
	texCoord = aTexCoord;
}