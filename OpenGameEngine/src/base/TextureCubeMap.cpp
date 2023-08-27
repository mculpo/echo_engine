#include <base/TextureCubeMap.h>
namespace openge {
	TextureCubeMap::TextureCubeMap(std::vector<String> paths) 
		: m_paths(paths) , m_textureType(TextureType::CubeMap)
	{
		Create();
	}
	TextureCubeMap::TextureCubeMap(std::vector<String> paths, TextureType textureType) 
		: m_paths(paths), m_textureType(textureType)
	{
		Create();
	}
	TextureCubeMap::~TextureCubeMap()
	{
	}
	void TextureCubeMap::Bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);
	}
	void TextureCubeMap::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
	unsigned int TextureCubeMap::GetId() const
	{
		return m_textureID;
	}
	void TextureCubeMap::Create()
	{
		glGenTextures(1, &m_textureID);
		Bind();
		LoadTextures();
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		/// 1. GL_TEXTURE_WRAP_S:
		//    Isso se refere à dimensão horizontal da textura.
		//    A constante GL_CLAMP_TO_EDGE indica que, quando a coordenada S (horizontal) for menor que 0 ou maior que 1,
		//    a textura será repetida, mas as partes repetidas serão preenchidas com os pixels da borda da textura.
		//    Isso evita que a textura repita seu padrão de forma visível.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		/// 2. GL_TEXTURE_WRAP_T:
		//    Isso se refere à dimensão vertical da textura.
		//    A constante GL_CLAMP_TO_EDGE tem o mesmo efeito aqui que no caso do GL_TEXTURE_WRAP_S.
		//    Quando a coordenada T (vertical) for menor que 0 ou maior que 1, a textura será repetida,
		//    mas as partes repetidas serão preenchidas com os pixels da borda da textura.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		/// 3. GL_TEXTURE_WRAP_R:
		//    Isso se refere à dimensão de profundidade (ou de outra forma, à terceira dimensão) da textura. Isso é relevante para texturas 3D.
		//    A constante GL_CLAMP_TO_EDGE age de forma similar às dimensões S e T, mas para a dimensão de profundidade.
		//    Ela define o comportamento de repetição em caso de coordenadas de profundidade menores que 0 ou maiores que 1.
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	// loads a cubemap texture from 6 individual texture faces
	// order:
	// +X (right)
	// -X (left)
	// +Y (top)
	// -Y (bottom)
	// +Z (front) 
	// -Z (back)
	// -------------------------------------------------------
	void TextureCubeMap::LoadTextures()
	{
		stbi_set_flip_vertically_on_load(false);
		int width, height, nrChannels;
		for (unsigned int i = 0; i < m_paths.size(); i++) {
			unsigned char* data = stbi_load(m_paths[i].c_str(), &width, &height, &nrChannels, 0);
			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else {
				std::cout << "Cubemap texture failed to load at path: " << m_paths[i] << std::endl;
				stbi_image_free(data);
			}
		}
	}
}