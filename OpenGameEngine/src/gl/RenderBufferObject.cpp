#include <gl/RenderBufferObject.h>

namespace openge {
	
	RenderBufferObject::RenderBufferObject()
	{
		glGenRenderbuffers(1, &m_rendererID);
		Bind();
		RenderBufferStorage();
		AttachmentFramebufferRenderBuffer();
	}

	void RenderBufferObject::RenderBufferStorage()
	{
		/*
		* glRenderbufferStorage: Essa fun��o � usada para alocar espa�o de armazenamento para um renderbuffer.
		* GL_RENDERBUFFER: Indica que estamos trabalhando com um renderbuffer.
		* GL_DEPTH24_STENCIL8: Especifica o formato de armazenamento para o renderbuffer. Neste caso, o renderbuffer ter� 24 bits para dados de profundidade e 8 bits para dados de est�ncil, totalizando 32 bits no total.
		*/
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
	}

	void RenderBufferObject::AttachmentFramebufferRenderBuffer()
	{
		/*
		* glFramebufferRenderbuffer: Essa fun��o � usada para anexar um renderbuffer a um framebuffer.
		* GL_FRAMEBUFFER: Indica que estamos anexando o renderbuffer ao framebuffer atualmente vinculado.
		* GL_DEPTH_STENCIL_ATTACHMENT: Especifica que o renderbuffer est� sendo anexado como um anexo de profundidade e est�ncil.
		* GL_RENDERBUFFER: Indica que o objeto sendo anexado � um renderbuffer.
		* m_rendererID: identificador (handle) do renderbuffer que est� sendo anexado ao framebuffer.
		*/
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rendererID);
	}

	void RenderBufferObject::Bind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_rendererID);
	}

	void RenderBufferObject::Unbind()
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}