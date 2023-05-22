#pragma once
#include "Engine.h"
namespace openge {

	enum VertexPointerEnum {
		VP_FLOAT = 0,
		VP_BITE,
		VP_INT
	};

	class VertexAttribPointerLayout {
	private:
		int m_size;
		VertexPointerEnum m_type;
	public:
		VertexAttribPointerLayout(int size, VertexPointerEnum type) : m_size(size), m_type(type) {}
		~VertexAttribPointerLayout() {};

		int getSize() {
			return m_size;
		}
		VertexPointerEnum getType() {
			return m_type;
		}
	
		static unsigned int getGLType(VertexPointerEnum vertexPointerEnum) {
			switch (vertexPointerEnum)
			{
			case openge::VP_FLOAT:
				return GL_FLOAT;
			case openge::VP_BITE:
				return GL_UNSIGNED_BYTE;
			case openge::VP_INT:
				return GL_INT;
			default:
				return 0;
			}
		}
	};

	

	
}