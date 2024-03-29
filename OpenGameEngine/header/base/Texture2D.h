#pragma once
#include <core/core.h>
namespace openge {

	enum class TextureType {
		Diffuse,
		Specular,
		Normal,
		Height,
		CubeMap
	};

	class Texture2D
	{
	public:
		Texture2D(const std::string& path);
		Texture2D(const std::string& path, TextureType textureType);
		Texture2D(const std::string& path, TextureType textureType, const std::string& name);
		~Texture2D();
		
		const TextureType GetTextureType() const;
		const String GetName() const;
		const String GetPath() const;

		void SetName(String name);

		void Bind();
		void Unbind();
		void LoadTexture(const std::string& path);
		unsigned int GetTexture() const;
	private:
		void CreateTexture(const std::string& path);
		void GenerateTexture(unsigned char* data, int width, int height);
	private:
		unsigned int m_rendererID;
		String m_path;
		String m_name;
		TextureType m_textureType;
		unsigned int m_format;
	};
}

