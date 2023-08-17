#ifndef __RENDERBUFFEROBJECT_H__
#define __RENDERBUFFEROBJECT_H__
#include <core/core.h>
namespace openge {
	class RenderBufferObject {
	private:
		unsigned int m_rendererID;
		void RenderBufferStorage();
		void AttachmentFramebufferRenderBuffer();
	public:
		RenderBufferObject();
		void Bind();
		void Unbind();
	};
}
#endif // !__RENDERBUFFEROBJECT_H__

