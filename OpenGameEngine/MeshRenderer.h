#ifndef __MESHRENDERER_H__
#define __MESHRENDERER_H__
#include <ecs/components/Component.h>
#include "Material.h"
#include <ecs/components/mesh/Mesh.h>
namespace openge {
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		MeshRenderer(Entity* entity);
		MeshRenderer(Entity* entity, Material* material, Mesh* mesh);
		~MeshRenderer();

		// Construtor de cópia
		MeshRenderer(const MeshRenderer& other)
			: Component(other), // Chama o construtor de cópia da classe base Component
			m_material(other.m_material ? std::make_unique<Material>(*other.m_material) : nullptr),
			m_mesh(other.m_mesh ? std::make_unique<Mesh>(*other.m_mesh) : nullptr)
		{
		}

		void setup();
		void bind();
		void render();

		std::shared_ptr<Material> setMaterial(std::shared_ptr<Material> material);
		void setMesh(std::shared_ptr<Mesh> mesh);

	private:
		std::shared_ptr<Material> m_material;
		std::shared_ptr<Mesh> m_mesh;
	};
}
#endif

