#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture; // Textura de cor
uniform vec2 resolution = vec2(1280, 720); // Tamanho do pixel (largura x altura)

// Tamanho da grade de pixelização
uniform float pixelSize = 3.5;

void main()
{
    // Calcula as coordenadas da textura para o pixel atual na resolução pixelizada
    //vec2 pixelCoords = floor(TexCoords * resolution / pixelSize) / (resolution / pixelSize);

    // Coleta a cor da textura de cor nas coordenadas do pixel
    //vec4 color = texture(screenTexture, pixelCoords);

    // Define a cor final do fragmento
    //FragColor = color;

    FragColor = vec4(texture(screenTexture, TexCoords).rgb, 1.0);
} 