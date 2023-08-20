#include <base/FrameBufferTexture.h>
namespace openge {
	FrameBufferTexture::FrameBufferTexture()
	{
		std::vector<VertexQuad> vertex = ShapeVerticesManager::getInstance().getQuadVertices();
		setVAO(createRef<VertexArrayObject>());
		setVBO(createRef<VertexBufferObject>(vertex.data(), vertex.size() * sizeof(Vertex), GL_STATIC_DRAW));
		m_vao->AddLayout(2, VP_FLOAT); // aPos
		m_vao->AddLayout(2, VP_FLOAT); // aTexCoords
		m_vao->runLayout();

		setFBO(createRef<FrameBufferObject>());
		setTCB(createRef<TextureColorBuffer>());
		setRBO(createRef<RenderBufferObject>());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		Unbind();
	}
	FrameBufferTexture::~FrameBufferTexture()
	{
	}
	void FrameBufferTexture::Draw()
	{
		Unbind();
		glDisable(GL_DEPTH_TEST);

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_shader->Bind();
		m_vao->Bind();
		m_tcb->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	void FrameBufferTexture::Bind()
	{
		m_fbo->Bind();
	}
	void FrameBufferTexture::Unbind()
	{
		m_fbo->Unbind();
	}
	void FrameBufferTexture::setVAO(ref<VertexArrayObject> vao)
	{
		m_vao = std::move(vao);
	}
	void FrameBufferTexture::setVBO(ref<VertexBufferObject> vbo)
	{
		m_vbo = std::move(vbo);
	}
	void FrameBufferTexture::setFBO(ref<FrameBufferObject> fbo)
	{
		m_fbo = std::move(fbo);
	}
	void FrameBufferTexture::setTCB(ref<TextureColorBuffer> tcb)
	{
		m_tcb = std::move(tcb);
	}
	void FrameBufferTexture::setRBO(ref<RenderBufferObject> rbo)
	{
		m_rbo = std::move(rbo);
	}
	void FrameBufferTexture::setShader(ref<Shader> shader)
	{
		m_shader = std::move(shader);
	}
}