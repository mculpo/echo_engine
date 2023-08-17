#include <gl/TextureColorBuffer.h>

namespace openge {
	TextureColorBuffer::TextureColorBuffer()
	{
		glGenTextures(1, &m_rendererID);
		Bind();
		ConfigTexture2D();
		AttachmentFrameBufferTexture2D();
	}

	void TextureColorBuffer::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_rendererID);
	}

	void TextureColorBuffer::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureColorBuffer::ConfigTexture2D()
	{
		/*
		* glTexImage2D: Essa fun��o � usada para definir os dados de uma textura 2D.
		* GL_TEXTURE_2D: Especifica que estamos trabalhando com uma textura 2D.
		* 0: N�vel de mipmap. Este � o n�vel base da textura, que � o n�vel de maior resolu��o.
		* GL_RGB: Indica o formato interno da textura. Neste caso, a textura armazenar� valores RGB (vermelho, verde e azul) para cada pixel.
		* WIDTH: A largura da textura em pixels.
		* HEIGHT: A altura da textura em pixels.
		* 0: Sempre deve ser 0. Era usado para especificar bordas, mas n�o � mais usado.
		* GL_RGB: O formato dos dados de entrada. Neste caso, os dados ser�o fornecidos em formato RGB.
		* GL_UNSIGNED_BYTE: O tipo de dados dos valores de cada canal de cor. Aqui, os valores ser�o representados como bytes n�o assinados (0-255).
		* NULL: Os dados iniciais da textura. Neste caso, estamos configurando a textura sem especificar dados iniciais. Isso � apropriado quando voc� deseja criar uma textura vazia para ser preenchida posteriormente.
		*/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		/*
		* @GL_TEXTURE_MIN_FILTER � um par�metro que controla a filtragem aplicada quando a textura � visualizada em um tamanho menor do que sua resolu��o original.
		* @GL_TEXTURE_MAG_FILTER � um par�metro que controla a filtragem aplicada quando a textura � visualizada em um tamanho maior do que sua resolu��o original.
		* @GL_LINEAR A filtragem linear suaviza a transi��o entre pixels, resultando em uma imagem mais suave ao reduzir o tamanho da textura ou proporcionando uma apar�ncia menos pixelada quando ampliada.
		*/
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void TextureColorBuffer::AttachmentFrameBufferTexture2D()
	{
		/*
		* @glFramebufferTexture2D: Esta fun��o � usada para anexar uma textura a um framebuffer.
		* @GL_FRAMEBUFFER: Indica que estamos anexando uma textura ao framebuffer atualmente vinculado.
		* @GL_COLOR_ATTACHMENT0: Especifica que a textura ser� usada como o primeiro anexo de cor. Em geral, um framebuffer pode ter v�rios anexos de cor, e GL_COLOR_ATTACHMENT0 refere-se ao primeiro deles.
		* @GL_TEXTURE_2D: Indica que estamos anexando uma textura bidimensional ao framebuffer.
		* @m_rendererID: Este � o identificador (handle) da textura que voc� deseja anexar ao framebuffer como um anexo de cor.
		* @0: N�vel de mipmap. Quando se trabalha com texturas com m�ltiplos n�veis de mipmap (n�veis de resolu��o diferentes), este valor especifica o n�vel de mipmap a ser anexado. No caso de 0, estamos usando o n�vel mais alto (resolu��o original) da textura.
		*/
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_rendererID, 0);
	}

	unsigned int TextureColorBuffer::getId() const
	{
		return m_rendererID;
	}
}