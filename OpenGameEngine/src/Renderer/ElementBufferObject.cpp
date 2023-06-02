#include "ElementBufferObject.h"
namespace openge {
	ElementBufferObject::ElementBufferObject(const void* indices, unsigned int size, unsigned int glEnum)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, glEnum);
	}
	ElementBufferObject::~ElementBufferObject()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void ElementBufferObject::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}
	void ElementBufferObject::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}