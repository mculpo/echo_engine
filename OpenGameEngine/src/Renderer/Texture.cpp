#include "Texture.h"
namespace openge {
	Texture::Texture(const std::string& path) : m_path(path), m_isRGBA(false), m_textureType(TextureType::Diffuse)
	{
		CreateTexture(path);
	}
	Texture::Texture(const std::string& path, TextureType textureType) : m_path(path), m_isRGBA(false), m_textureType(textureType)
	{
		CreateTexture(path);
	}
	Texture::Texture(const std::string& path, bool rgba) : m_path(path), m_isRGBA(rgba), m_textureType(TextureType::Diffuse)
	{
		CreateTexture(path);
	}
	Texture::~Texture()
	{
	}
	const TextureType Texture::GetTextureType() const
	{
		return m_textureType;
	}
	const String Texture::GetName() const
	{
		return m_name;
	}
	const String Texture::GetPath() const
	{
		return m_path;
	}
	void Texture::SetName(String name)
	{
		m_name = name;
	}
	void Texture::CreateTexture(const std::string& path)
	{
		glGenTextures(1, &m_rendererID);
		Bind();
		/**
		* GL_TEXTURE_WRAP_S - Define o parâmetro wrap para coordenadas de textura s como GL_CLAMP ou GL_REPEAT. GL_CLAMP faz com que as coordenadas s sejam fixadas ao intervalo [0,1] e é útil para impedir a quebra de artefatos ao mapear uma única imagem em um objeto. GL_REPEAT faz com que a parte inteira da coordenada s seja ignorada; O OpenGL usa apenas a parte fracionária, criando assim um padrão de repetição. Os elementos de textura de borda são acessados somente se a quebra estiver definida como GL_CLAMP. Inicialmente, GL_TEXTURE_WRAP_S é definido como GL_REPEAT.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X
		/**
		* GL_TEXTURE_WRAP_T - Define o parâmetro wrap para a coordenada de textura t como GL_CLAMP ou GL_REPEAT. Inicialmente, GL_TEXTURE_WRAP_T é definido como GL_REPEAT
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y
		// Minimização de textura GL_TEXTURE_MIN_FILTER
		/**
		* GL_LINEAR (também conhecida como filtragem (bi)linear) obtém um valor interpolado dos texels vizinhos da coordenada de textura, aproximando-se de uma cor entre os texels. Quanto menor a distância da coordenada de textura ao centro de um texel, mais a cor do texel contribui para a cor amostrada.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		/*
		* GL_TEXTURE_MAG_FILTER A função de ampliação de textura é usada quando o pixel que está sendo texturizado é mapeado para uma área menor ou igual a um elemento de textura. Ele define a função de ampliação de textura para GL_NEAREST ou GL_LINEAR.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		LoadTexture(path);
	}
	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_rendererID);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void Texture::LoadTexture(const std::string& path)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			GenerateTexture(data, width, height);
		}
		else {
			std::cout << "Falhar ao carregar textura" << std::endl;
		}
		//free memory imagem
		stbi_image_free(data);
	}
	unsigned int Texture::GetTexture() const
	{
		return m_rendererID;
	}
	void Texture::GenerateTexture(unsigned char* data, int width, int height)
	{
		glTexImage2D(	GL_TEXTURE_2D, 
						0,
						m_isRGBA ? GL_RGBA : GL_RGB,
						width, 
						height, 
						0, 
						m_isRGBA ? GL_RGBA : GL_RGB,
						GL_UNSIGNED_BYTE, 
						data
		);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}
