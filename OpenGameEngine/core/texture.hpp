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
		String mPath;
		String mName;
		Type mType;
		unsigned int mFormat;
	};

#ifndef OPENGE_TEXTUREMANAGER
#define OPENGE_TEXTUREMANAGER


	void createTexture2D(Texture* pTexture, const std::string& path) {

	}

#endif
}
#endif
