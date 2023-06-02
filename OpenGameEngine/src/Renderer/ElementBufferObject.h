#pragma once
#include <Core/tspch.h>
namespace openge {
	class ElementBufferObject
	{
	private:
		unsigned int m_rendererID;
	public:
		ElementBufferObject(const void* indices, unsigned int size, unsigned int glEnum);
		~ElementBufferObject();
		void Bind();
		void Unbind();
	};
}

