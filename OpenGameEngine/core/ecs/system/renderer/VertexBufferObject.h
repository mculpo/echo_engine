#pragma once
namespace openge {
	class VertexBufferObject
	{
		public:
			VertexBufferObject(const void* data, unsigned int size, unsigned int glEnum);
			~VertexBufferObject();
			void Bind();
			void Unbind();
	private:
		unsigned int m_rendererID;
	};
}

