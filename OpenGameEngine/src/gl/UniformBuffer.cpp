#include <gl/UniformBuffer.h>
namespace openge {
	UniformBuffer::UniformBuffer(String uniformBlockName, unsigned int bufferSize, unsigned int bindingPoint) :
		m_uniformBlockName(uniformBlockName), m_bufferSize(bufferSize), m_currentOffset(0), m_bindingPoint(bindingPoint)
	{
		glGenBuffers(1, &m_uniformBufferId);
		Bind();
		glBufferData(GL_UNIFORM_BUFFER, m_bufferSize, NULL, GL_STATIC_DRAW);
		Unbind();
	}

	UniformBuffer::~UniformBuffer()
	{
	}

	void UniformBuffer::Bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferId);
	}

	void UniformBuffer::Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::BindToBlock(unsigned int shaderProgramId) 
	{
		unsigned int uniformBlockIndex = glGetUniformBlockIndex(shaderProgramId, m_uniformBlockName.c_str());
		glUniformBlockBinding(shaderProgramId, uniformBlockIndex, m_bindingPoint);
	}

	void UniformBuffer::BindBufferRange()
	{
		/*
		* GL_UNIFORM_BUFFER: Esse parâmetro define o alvo de ligação do buffer. Pode ser um dos seguintes valores: GL_UNIFORM_BUFFER: Indica que o buffer será usado como um buffer de dados uniformes. Outros valores podem ser usados para diferentes tipos de buffers, como GL_ARRAY_BUFFER ou GL_ELEMENT_ARRAY_BUFFER.
		* m_bindingPoint: Esse é o índice do ponto de ligação no qual você deseja associar o buffer. É um valor inteiro não negativo.
		* m_uniformBufferId: É o ID do buffer OpenGL que você deseja associar ao ponto de ligação especificado. Você deve ter criado e gerado esse buffer usando glGenBuffers() antes de poder associá-lo aqui.
		* 0 / offset: Esse é o deslocamento em bytes a partir do início do buffer que você deseja usar para esta ligação. É um valor do tipo GLintptr, que é um tipo inteiro de tamanho suficiente para armazenar ponteiros e deslocamentos de memória.
		* m_bufferSize: É o tamanho dos dados que você deseja associar a essa ligação. É um valor do tipo GLsizeiptr, que é um tipo inteiro de tamanho suficiente para armazenar tamanhos de memória.
		*/
		glBindBufferRange(GL_UNIFORM_BUFFER, m_bindingPoint, m_uniformBufferId, 0, m_bufferSize);
	}

	void UniformBuffer::Update(unsigned int offset, unsigned int dataSize, const void* data)
	{
		if (offset + dataSize <= m_bufferSize) {
			glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBufferId);
			glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		else {
			std::cerr << "Error: Data update exceeds buffer size." << std::endl;
		}
	}
}