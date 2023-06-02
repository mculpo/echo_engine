#include "VertexBufferObject.h"
namespace openge {
	VertexBufferObject::VertexBufferObject(const void* data, unsigned int size ,unsigned int glEnum)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, glEnum);
	}
	VertexBufferObject::~VertexBufferObject()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void VertexBufferObject::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}
	void VertexBufferObject::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
