#include <base/InstancedBuffer.h>
namespace openge {
	InstancedBuffer::InstancedBuffer()
	{
	}
	void InstancedBuffer::SetMaterial(ref<Material> material)
	{
		m_material = material;
	}
	void InstancedBuffer::SetGameObjects(std::vector<ref<GameObject>> gameobjects)
	{
		m_object = gameobjects;
	}
	void InstancedBuffer::AddGameObject(ref<GameObject> gameobject)
	{
		m_object.push_back(gameobject);
	}
	void InstancedBuffer::Bind()
	{
		PrepareInstacedObjects();
		CreateVBOBuffer();
		ConfigureInstancedAttributes();
		m_material->SetAmountInstancedObject(m_object.size());
	}
	void InstancedBuffer::PrepareInstacedObjects()
	{
		m_model = new Matrix4[m_object.size()];
		for (unsigned int i = 0; i < m_object.size(); i++)
		{
			Matrix4 model = m_object[i]->getTransform()->getModelMatrix();
			m_model[i] = model;
		}
	}
	void InstancedBuffer::CreateVBOBuffer()
	{
		m_VBO = createRef<VertexBufferObject>(&m_model[0], m_object.size() * sizeof(Matrix4), GL_STATIC_DRAW);
	}
	void InstancedBuffer::ConfigureInstancedAttributes()
	{
		for (unsigned int i = 0; i < m_object.size(); i++)
		{
			std::vector<Mesh> meshs = m_object[i]->getRenderer()->GetMeshs();
			for (unsigned int j = 0; j < meshs.size(); j++) {

				unsigned int vao = meshs[j].GetVAO()->GetId();
				glBindVertexArray(vao);
				// set attribute pointers for matrix (4 times vec4)
				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)0);
				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(sizeof(Vector4)));
				glEnableVertexAttribArray(7);
				glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(2 * sizeof(Vector4)));
				glEnableVertexAttribArray(8);
				glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(3 * sizeof(Vector4)));

				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);
				glVertexAttribDivisor(7, 1);
				glVertexAttribDivisor(8, 1);

				glBindVertexArray(0);
			}
		}
	}
	unsigned int InstancedBuffer::GetAmountModel()
	{
		unsigned int currentModels = 0;
		for (unsigned int i = 0; i < m_object.size(); i++)
		{
			currentModels += m_object[i]->getRenderer()->GetMeshs().size();
		}
		return currentModels;
	}
}