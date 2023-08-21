#include <base/TextureCubeMap.h>

namespace openge {
	TextureCubeMap::TextureCubeMap()
	{
	}
	TextureCubeMap::TextureCubeMap(std::vector<String> paths) : m_paths(std::move(paths))
	{
		glGenTextures(1, &m_textureId);
		Bind();
		LoadCubeMap();
	}

	TextureCubeMap::~TextureCubeMap() {}

	void TextureCubeMap::Bind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureId);
	}

	void TextureCubeMap::Unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void TextureCubeMap::LoadCubeMap()
	{
		stbi_set_flip_vertically_on_load(false);
		if (m_paths.size() != 6) {
			std::cout << "Cubemap texture must have 6 path texture configurated." << std::endl;
			std::cout << "Current paths configurated: " << m_paths.size() << std::endl;
			return;
		}
		int width, height, nrChannels;
		for (unsigned int i = 0; i < m_paths.size(); i++)
		{
			unsigned char* data = stbi_load(m_paths[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	unsigned int TextureCubeMap::GetId()
	{
		return m_textureId;
	}

	void TextureCubeMap::SetPath(String& path)
	{
		m_paths.push_back(path);
	}

	void TextureCubeMap::SetPaths(std::vector<String> paths)
	{
		m_paths.insert(m_paths.end(), paths.begin(), paths.end());
	}

	std::vector<String> TextureCubeMap::GetPaths() const
	{
		return m_paths;
	}
}