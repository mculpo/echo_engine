#pragma once
#include <Core/tspch.h>
namespace openge {
	class Texture
	{
	public:
		Texture(const std::string& path);
		Texture(const std::string& path, bool rgba);
		~Texture();
		
		void Bind();
		void Unbind();
		void LoadTexture(const std::string& path);
		unsigned int GetTexture() const;
	private:
		void CreateTexture(const std::string& path);
		void GenerateTexture(unsigned char* data, int width, int height);
	private:
		unsigned int m_rendererID;
		bool m_isRGBA;
	};
}

