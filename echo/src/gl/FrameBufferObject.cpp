#include <gl/FrameBufferObject.h>

namespace openge {
	FrameBufferObject::FrameBufferObject()
	{
		glGenFramebuffers(1, &m_rendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
	}
	void FrameBufferObject::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
	}
	void FrameBufferObject::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	unsigned int FrameBufferObject::getId() const
	{
		return m_rendererID;
	}
}