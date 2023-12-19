#ifndef OPENGE_TEXTURE
#define OPENGE_TEXTURE
#include <core/core.h>
namespace openge::texture {

	enum Type {
		Diffuse,
		Specular,
		Normal,
		Height,
		CubeMap
	};

	struct Texture {
		unsigned int mTextureID;
		Type mType;
	};

#ifndef OPENGE_TEXTUREMANAGER
#define OPENGE_TEXTUREMANAGER

	void createTexture2D(Texture* pTexture, const std::string& path) {

		glGenTextures(1, &pTexture->mTextureID);

		bind(pTexture);

		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		unsigned int m_format = GL_RGB;
		if (data) {

			if (nrChannels == 1)
				m_format = GL_RED;
			else if (nrChannels == 3)
				m_format = GL_RGB;
			else if (nrChannels == 4)
				m_format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Falhar ao carregar textura" << std::endl;
		}
		
		stbi_image_free(data);

		/**
		* GL_TEXTURE_WRAP_S - Define o par�metro wrap para coordenadas de textura s como GL_CLAMP ou GL_REPEAT. GL_CLAMP faz com que as coordenadas s sejam fixadas ao intervalo [0,1] e � �til para impedir a quebra de artefatos ao mapear uma �nica imagem em um objeto. GL_REPEAT faz com que a parte inteira da coordenada s seja ignorada; O OpenGL usa apenas a parte fracion�ria, criando assim um padr�o de repeti��o. Os elementos de textura de borda s�o acessados somente se a quebra estiver definida como GL_CLAMP. Inicialmente, GL_TEXTURE_WRAP_S � definido como GL_REPEAT.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_format == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT); // X
		/**
		* GL_TEXTURE_WRAP_T - Define o par�metro wrap para a coordenada de textura t como GL_CLAMP ou GL_REPEAT. Inicialmente, GL_TEXTURE_WRAP_T � definido como GL_REPEAT
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_format == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT); // Y
		/**
		* // Minimiza��o de textura GL_TEXTURE_MIN_FILTER
		* GL_LINEAR (tamb�m conhecida como filtragem (bi)linear) obt�m um valor interpolado dos texels vizinhos da coordenada de textura, aproximando-se de uma cor entre os texels. Quanto menor a dist�ncia da coordenada de textura ao centro de um texel, mais a cor do texel contribui para a cor amostrada.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		/*
		* GL_TEXTURE_MAG_FILTER A fun��o de amplia��o de textura � usada quando o pixel que est� sendo texturizado � mapeado para uma �rea menor ou igual a um elemento de textura. Ele define a fun��o de amplia��o de textura para GL_NEAREST ou GL_LINEAR.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	}

	void createTextureCubeMap(Texture* pTexture, std::vector<String> paths) {

		glGenTextures(1, &pTexture->mTextureID);

		bind(pTexture);

		stbi_set_flip_vertically_on_load(false);
		int width, height, nrChannels;
		for (unsigned int i = 0; i < paths.size(); i++) {
			unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {
				std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
				stbi_image_free(data);
			}
		}
		//GL_TEXTURE_CUBE_MAP
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		/// 1. GL_TEXTURE_WRAP_S:
		//    Isso se refere � dimens�o horizontal da textura.
		//    A constante GL_CLAMP_TO_EDGE indica que, quando a coordenada S (horizontal) for menor que 0 ou maior que 1,
		//    a textura ser� repetida, mas as partes repetidas ser�o preenchidas com os pixels da borda da textura.
		//    Isso evita que a textura repita seu padr�o de forma vis�vel.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		/// 2. GL_TEXTURE_WRAP_T:
		//    Isso se refere � dimens�o vertical da textura.
		//    A constante GL_CLAMP_TO_EDGE tem o mesmo efeito aqui que no caso do GL_TEXTURE_WRAP_S.
		//    Quando a coordenada T (vertical) for menor que 0 ou maior que 1, a textura ser� repetida,
		//    mas as partes repetidas ser�o preenchidas com os pixels da borda da textura.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		/// 3. GL_TEXTURE_WRAP_R:
		//    Isso se refere � dimens�o de profundidade (ou de outra forma, � terceira dimens�o) da textura. Isso � relevante para texturas 3D.
		//    A constante GL_CLAMP_TO_EDGE age de forma similar �s dimens�es S e T, mas para a dimens�o de profundidade.
		//    Ela define o comportamento de repeti��o em caso de coordenadas de profundidade menores que 0 ou maiores que 1.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void bind(Texture* pTexture ) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, pTexture->mTextureID);
	}

	void unbind(Texture* pTexture) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

#endif
}
#endif
