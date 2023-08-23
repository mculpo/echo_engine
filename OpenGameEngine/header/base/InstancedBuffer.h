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
		void SetGameObjects(std::vector<ref<GameObject>> gameobjects);
		void AddGameObject(ref<GameObject> gameobject);

		void Bind();

	private:
		ref<VertexBufferObject> m_VBO;
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
