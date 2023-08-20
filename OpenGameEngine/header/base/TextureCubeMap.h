#ifndef __TEXTURECUBEMAP_H__
#define __TEXTURECUBEMAP_H__
#include <core/core.h>7

namespace openge {
	class TextureCubeMap {
	public:
		TextureCubeMap();
		TextureCubeMap(std::vector<String> paths);

		
		void Bind();
		void Unbind();
		void LoadCubeMap();

		unsigned int GetId();

		void SetPath(String& path);
		void SetPaths(std::vector<String> paths);
		std::vector<String> GetPaths() const;
	private:
		unsigned int m_rendererID;
		std::vector<String> m_paths;
	};
}

#endif // !__TEXTURECUBEMAP_H__
