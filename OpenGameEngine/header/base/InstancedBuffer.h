#ifndef __INSTANCEDBUFFER_H__
#define __INSTANCEDBUFFER_H__
#include <core/core.h>
#include <gl/VertexBufferObject.h>
#include <base/Mesh.h>
#include <entity/GameObject.h>
namespace openge {
	class InstancedBuffer : public Singleton<InstancedBuffer> {
	public:
		InstancedBuffer();

		void SetMaterial(ref<Material> material);
		void SetMesh(std::vector<Mesh> mesh);
		void SetGameObjects(std::vector<ref<GameObject>> gameobjects);
		void AddGameObject(ref<GameObject> gameobject);

		void Bind();
		void UpdateInstanced();

	private:
		ref<VertexBufferObject> m_VBO;
		std::vector<Mesh> m_meshs;
		ref<Material> m_material;
		std::vector<ref<GameObject>> m_object;
		Matrix4* m_model;

		unsigned int GetAmountModel();
		void PrepareInstacedObjects();
		void CreateVBOBuffer();
		void ConfigureInstancedAttributes();
	};
}
#endif // !__INSTANCEDBUFFER_H__
