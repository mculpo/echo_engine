#ifndef __RENDERER_H__
#define __RENDERER_H__
#include <Component/Component.h>
#include <Component/Material.h>
#include <Component/Mesh.h>
#include <Component/Transform.h>
#include <Renderer/Camera.h>
#include <Entity/GameObject.h>
namespace openge {
	class Renderer : public Component
	{
	public:
		Renderer() {}
		~Renderer() {}

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

