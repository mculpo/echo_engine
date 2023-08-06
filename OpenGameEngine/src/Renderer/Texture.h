#pragma once
#include <Core/tspch.h>
namespace openge {

	enum class TextureType {
		Diffuse,
		Specular,
		Normal,
		Height
	};

	class Texture
	{
	public:
		Texture(const std::string& path);
		Texture(const std::string& path, TextureType textureType);
		Texture(const std::string& path, bool rgba);
		~Texture();
		
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
		bool m_isRGBA;
	};
}

