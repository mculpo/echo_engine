#include <gl/VertexArrayObject.h>

namespace openge {
	VertexArrayObject::VertexArrayObject() : m_stride(0)
	{
		glGenVertexArrays(1, &m_rendererID);
		glBindVertexArray(m_rendererID);
	}
	VertexArrayObject::~VertexArrayObject()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}
	void VertexArrayObject::Bind()
	{
		glBindVertexArray(m_rendererID);
	}
	void VertexArrayObject::Unbind()
	{
		glBindVertexArray(0);
	}
	void VertexArrayObject::AddLayout(VertexAttribPointerLayout layout)
	{
		m_layout.push_back(layout); 
		m_stride += layout.getSize();
	}
	void VertexArrayObject::AddLayout(int size, VertexPointerEnum type)
	{
		std::unique_ptr<VertexAttribPointerLayout> vertex = std::make_unique<VertexAttribPointerLayout>(size, type);
		m_layout.push_back(*vertex);
		m_stride += vertex->getSize();
	}
	void VertexArrayObject::runLayout()
	{
		int _layoutCount = 0;
		int _size = 0;
		Bind();
		for (auto& l : m_layout) {
			glEnableVertexAttribArray(_layoutCount);
			glVertexAttribPointer(	_layoutCount, 
									l.getSize(), 
									VertexAttribPointerLayout::getGLType(l.getType()), 
									GL_FALSE, 
									m_stride * sizeof(float), 
									(void*) (_size * sizeof(float))
			);
			_layoutCount++;
			_size += l.getSize();
		}
	}
	void VertexArrayObject::disableLayout()
	{
		int _layoutCount = 0;
		for (auto& l : m_layout) {
			glDisableVertexAttribArray(_layoutCount);
			_layoutCount++;
		}
	}
	unsigned int VertexArrayObject::GetId()
	{
		return m_rendererID;
	}
}