#ifndef __FRAMEBUFFERTEXTURE_H__
#define __FRAMEBUFFERTEXTURE_H__
#include <core/core.h>
#include <gl/VertexArrayObject.h>
#include <gl/VertexBufferObject.h>
#include <gl/ElementBufferObject.h>
#include <gl/FrameBufferObject.h>
#include <gl/TextureColorBuffer.h>
#include <gl/RenderBufferObject.h>
#include <manager/ShapeVerticesManager.h>
#include <base/Shader.h>
namespace openge {
	class FrameBufferTexture {
	private:
		ref<FrameBufferObject> m_fbo;
		ref<TextureColorBuffer> m_tcb;
		ref<RenderBufferObject> m_rbo;
		
		ref<VertexArrayObject> m_vao;
		ref<VertexBufferObject> m_vbo;

		ref<Shader> m_shader;
	public:
		FrameBufferTexture();
		~FrameBufferTexture();

		void Draw();
		void Bind();
		void Unbind();

		void setVAO(ref<VertexArrayObject> vao);
		void setVBO(ref<VertexBufferObject> vbo);

		void setFBO(ref<FrameBufferObject> fbo);
		void setTCB(ref<TextureColorBuffer> tcb);
		void setRBO(ref<RenderBufferObject> rbo);

		void setShader(ref<Shader> shader);

	};
}
#endif // !__FRAMEBUFFERTEXTURE_H__
