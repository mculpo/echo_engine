#ifndef __UNIFORMBUFFER_H__
#define __UNIFORMBUFFER_H__
#include <core/core.h>
namespace openge {
	class UniformBuffer {
	public:
		UniformBuffer(String uniformBlockName,unsigned int bufferSize, unsigned int bindingPoint);
		~UniformBuffer();

		void Bind();
		void Unbind();
		void BindToBlock(unsigned int shaderProgramId);
		void BindBufferRange();
		void Update(unsigned int offset, unsigned int dataSize, const void* data);
	private:
		unsigned int m_uniformBufferId;
		unsigned int m_bindingPoint;
		unsigned int m_bufferSize;
		unsigned int m_currentOffset;
		String m_uniformBlockName;
	};
}
#endif // !__UNIFORMBUFFER_H__
