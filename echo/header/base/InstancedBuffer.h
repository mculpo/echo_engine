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
		void SetMesh(std::vector<ref<Mesh>> mesh);
		void SetGameObjects(std::vector<ref<GameObject>> gameobjects);
		void AddGameObject(ref<GameObject> gameobject);

		void InicializeInstanced();
		void VBOInstancedBind();
		void UpdateInstanced();

	private:
		ref<VertexBufferObject> m_VBO;
		std::vector<ref<Mesh>> m_meshs;
		ref<Material> m_material;
		std::vector<ref<GameObject>> m_object;

		unsigned int GetAmountModel();
		void PrepareInstacedObjects(Matrix4* m_model);
		void CreateVBOBuffer(Matrix4* m_model);
		void ConfigureInstancedAttributes();
	};
}
#endif // !__INSTANCEDBUFFER_H__
