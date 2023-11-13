#pragma once
#include <core/core.h>
#include <core/Vertex.h>
#include <gl/VertexAttribPointerLayout.h>
/*
* https://docs.gl/gl4/glVertexAttribPointer
*/
namespace openge {
	

	class VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();
		void Bind();
		void Unbind();
		void AddLayout(VertexAttribPointerLayout layout);
		void AddLayout(int size, VertexPointerEnum type);
		void runLayout();
		void disableLayout();

		unsigned int GetId();
	private:
		unsigned int m_rendererID;
		/*
		* Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
		*/
		int m_stride;
		std::vector<VertexAttribPointerLayout> m_layout;
	};
}

