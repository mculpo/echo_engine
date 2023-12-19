#ifndef OPENGE_VERTEX_BUFFER_OBJECT
#define OPENGE_VERTEX_BUFFER_OBJECT
#include <core/core.h>
namespace openge::gl::vao {
	struct VertexArrayObject {
		unsigned int mRendererID;
	};
#ifndef OPENGE_VERTEX_BUFFER_OBJECT_MANAGER
#define OPENGE_VERTEX_BUFFER_OBJECT_MANAGER

	void create(VertexArrayObject* pVao) {
		glGenVertexArrays(1, &pVao->mRendererID);
		glBindVertexArray(pVao->mRendererID);
	}

	void remove(VertexArrayObject* pVao) {
		glDeleteVertexArrays(1, &pVao->mRendererID);
	}

	void bind(VertexArrayObject* pVao) {
		glBindVertexArray(pVao->mRendererID);
	}

	void unbind() {
		glBindVertexArray(0);
	}
	/**
	* Exempl:
	*		glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)0);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(sizeof(Vector4)));
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(2 * sizeof(Vector3)));
	*/
	void attributeDate(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei	stride, const GLvoid* pointer) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}

	void attributeDisable(GLuint index) {
		glDisableVertexAttribArray(index);
	}

#endif
}
#endif
