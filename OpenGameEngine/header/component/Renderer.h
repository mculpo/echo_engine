#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <component/Component.h>
#include <component/Transform.h>
#include <component/Camera.h>

#include <base/Material.h>
#include <base/Mesh.h>

namespace openge {
	class Renderer : public Component
	{
	public:
		Renderer() {}
		~Renderer() {}

		virtual void bind() = 0;
		virtual void render() = 0;

		void addMesh(Mesh mesh);
		void setMeshs(std::vector<Mesh> mesh);
		void setMaterial(ref<Material> material);
		void setTransform(ref<Transform> transform);
		void setMainCamera(ref<Camera> camera);

		std::vector<Mesh> getMeshs();
		ref<Material> getMaterial();

	protected:
		std::vector<Mesh> m_meshs;
		ref<Material> m_material;
		ref<Camera> m_mainCamera;
		ref<Transform> m_transform;
	};
}
#endif

