#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__
#include <Component/Component.h>
#include <Component/Material.h>
#include <Component/Mesh.h>
#include <Component/Transform.h>
#include <Renderer/Camera.h>
#include <Entity/GameObject.h>
namespace openge {
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() {}
		~MeshRenderer() {}

		void setup();
		void bind();
		void render();

		void setMaterial(std::shared_ptr<Material> material);
		void setMesh(std::shared_ptr<Mesh> mesh);

	private:
		std::shared_ptr<Material> m_material;
		std::shared_ptr<Mesh> m_mesh;
	};
}
#endif

