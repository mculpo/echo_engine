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
		* GL_UNIFORM_BUFFER: Esse par�metro define o alvo de liga��o do buffer. Pode ser um dos seguintes valores: GL_UNIFORM_BUFFER: Indica que o buffer ser� usado como um buffer de dados uniformes. Outros valores podem ser usados para diferentes tipos de buffers, como GL_ARRAY_BUFFER ou GL_ELEMENT_ARRAY_BUFFER.
		* m_bindingPoint: Esse � o �ndice do ponto de liga��o no qual voc� deseja associar o buffer. � um valor inteiro n�o negativo.
		* m_uniformBufferId: � o ID do buffer OpenGL que voc� deseja associar ao ponto de liga��o especificado. Voc� deve ter criado e gerado esse buffer usando glGenBuffers() antes de poder associ�-lo aqui.
		* 0 / offset: Esse � o deslocamento em bytes a partir do in�cio do buffer que voc� deseja usar para esta liga��o. � um valor do tipo GLintptr, que � um tipo inteiro de tamanho suficiente para armazenar ponteiros e deslocamentos de mem�ria.
		* m_bufferSize: � o tamanho dos dados que voc� deseja associar a essa liga��o. � um valor do tipo GLsizeiptr, que � um tipo inteiro de tamanho suficiente para armazenar tamanhos de mem�ria.
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