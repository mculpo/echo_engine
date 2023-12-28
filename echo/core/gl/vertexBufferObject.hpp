#ifndef OPENGE_VERTEX_BUFFER_OBJECT
#define OPENGE_VERTEX_BUFFER_OBJECT
#include <core/core.h>
namespace echo::gl {
	struct VertexBufferObject
	{
		unsigned int mRendererID;
	};
}
#ifndef OPENGE_VERTEX_BUFFER_OBJECT_MANAGER
#define OPENGE_VERTEX_BUFFER_OBJECT_MANAGER
namespace echo::gl::vbo {
	void create(VertexBufferObject* pVBO,const void* data, unsigned int size, unsigned int glEnum) {
		glGenBuffers(1, &pVBO->mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, pVBO->mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, glEnum);
	}
	
	void remove(VertexBufferObject* pVBO) {
		glDeleteBuffers(1, &pVBO->mRendererID);
	}

	void bind(VertexBufferObject* pVBO) {
		glBindBuffer(GL_ARRAY_BUFFER, pVBO->mRendererID);
	}

	void unbind(VertexBufferObject* pVBO) {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
#endif
}
#endif
