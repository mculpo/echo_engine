#ifndef __TEXTURECOLORBUFFER_H__
#define __TEXTURECOLORBUFFER_H__
#include <core/core.h>
namespace openge {
	class TextureColorBuffer {
	private:
		unsigned int m_rendererID;
		void ConfigTexture2D();
		void AttachmentFrameBufferTexture2D();
	public:
		TextureColorBuffer();
		void Bind();
		void Unbind();
		unsigned int getId() const;
	};
}

#endif // !__TEXTURECOLORBUFFER_H__

