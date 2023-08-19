#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;

// texture samplers
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;
uniform sampler2D height;

void main()
{
    vec4 frag = (texture(specular, TexCoords) * texture(normal, TexCoords));
    FragColor = (texture(diffuse, TexCoords));
}
