#ifndef __FRAMEBUFFEROBJECT_H__
#define __FRAMEBUFFEROBJECT_H__
#include <core/core.h>
namespace openge {
	class FrameBufferObject {
	private:
		unsigned int m_rendererID;
	public:
		FrameBufferObject();
		void Bind();
		void Unbind();
		unsigned int getId() const;
	};
}

#endif // !__FRAMEBUFFEROBJECT_H__

