#ifndef OPENGE_ELEMENT_BUFFER_OBJECT
#define OPENGE_ELEMENT_BUFFER_OBJECT
#include <core/core.h>
namespace echo::gl {
	struct ElementBufferObject {
		unsigned int mRendererID;
	};
}
namespace echo::gl::ebo {
#ifndef OPENGE_ELEMENT_BUFFER_OBJECT_MANAGER
#define OPENGE_ELEMENT_BUFFER_OBJECT_MANAGER
	void create(ElementBufferObject* pEbo, unsigned int size, const void* indices, unsigned int glEnum) {
		glGenBuffers(1, &pEbo->mRendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pEbo->mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, glEnum);
	}

	void remove(ElementBufferObject* pEbo) {
		glDeleteBuffers(1, &pEbo->mRendererID);
	}

	void bind(ElementBufferObject* pEbo) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pEbo->mRendererID);
	}

	void unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
#endif
}
#endif
