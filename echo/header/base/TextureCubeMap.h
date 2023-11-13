#ifndef __TEXTURECUBEMAP_H__
#define __TEXTURECUBEMAP_H__
#include <core/core.h>
#include "Texture2D.h"
namespace openge {
	class TextureCubeMap
	{
	public:
		TextureCubeMap(std::vector<String> paths);
		TextureCubeMap(std::vector<String> paths, TextureType textureType);
		~TextureCubeMap();

		void Bind();
		void Unbind();
		
		unsigned int GetId() const;

	private:
		unsigned int m_textureID;
		std::vector<String> m_paths;
		TextureType m_textureType;

		void Create();
		void LoadTextures();
	};
}

#endif // __TEXTURECUBEMAP_H__



