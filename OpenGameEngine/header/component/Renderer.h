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

		virtual void Bind() = 0;
		virtual void Render() = 0;

		void AddMesh(ref <Mesh> mesh);
		void SetMeshs(std::vector<ref<Mesh>> mesh);
		void SetMaterial(ref<Material> material);
		void SetTransform(ref<Transform> transform);
		void SetMainCamera(ref<Camera> camera);

		std::vector<ref<Mesh>> GetMeshs();
		ref<Material> GetMaterial();

	protected:
		std::vector<ref<Mesh>> m_meshs;
		ref<Material> m_material;
		ref<Camera> m_mainCamera;
		ref<Transform> m_transform;
	};
}
#endif

