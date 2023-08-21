#ifndef __SKYBOX_H__
#define __SKYBOX_H__
#include <core/core.h>
#include <gl/VertexBufferObject.h>
#include <gl/VertexArrayObject.h>
#include <base/Material.h>
#include <base/TextureCubeMap.h>
#include <manager/ShapeVerticesManager.h>
#include <manager/TextureManager.h>
#include <component/Camera.h>
namespace openge {
	class Skybox {
	public:
		Skybox(ref<Material> material, std::vector<String> pathTexture, ref<Camera> mainCamera);
		~Skybox();

		void Setup();
		void Draw();
		void Bind();
		void BindTexture();
		void Unbind();

		void setVAO(ref<VertexArrayObject> vao);
		void setVBO(ref<VertexBufferObject> vbo);
		void setMaterial(ref<Material> material);
		void setMainCamera(ref<Camera> camera);
	private:
		ref<VertexBufferObject> m_vbo;
		ref<VertexArrayObject> m_vao;

		ref<Camera> m_mainCamera;
		ref<Material> m_material;
		std::vector<String> m_path_textures;
		ref<TextureCubeMap> m_textureCubeMap;
	};
}
#endif // !__SKYBOX_H__
