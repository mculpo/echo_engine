#include <base/InstancedBuffer.h>
namespace openge {
	InstancedBuffer::InstancedBuffer()
	{
	}
	void InstancedBuffer::SetMaterial(ref<Material> material)
	{
		m_material = material;
	}
	void InstancedBuffer::SetMesh(std::vector<ref<Mesh>> mesh)
	{
		m_meshs = mesh;
	}
	void InstancedBuffer::SetGameObjects(std::vector<ref<GameObject>> gameobjects)
	{
		m_object = gameobjects;
	}
	void InstancedBuffer::AddGameObject(ref<GameObject> gameobject)
	{
		m_object.push_back(gameobject);
	}

	void InstancedBuffer::InicializeInstanced()
	{
		Matrix4* m_model = new Matrix4[m_object.size()];
		PrepareInstacedObjects(m_model);
		CreateVBOBuffer(m_model);
		ConfigureInstancedAttributes();
		m_material->SetAmountInstancedObject(m_object.size());
	}

	void InstancedBuffer::VBOInstancedBind()
	{
		m_VBO->Bind();
	}

	void InstancedBuffer::UpdateInstanced()
	{
		m_material->getShader()->Bind();
		for (auto& mesh : m_meshs) {
			mesh->bindTexture(m_material);
			mesh->useVAO();
			glDrawElementsInstanced(
				GL_TRIANGLES,
				static_cast<unsigned int>(mesh->GetIndices().size()),
				GL_UNSIGNED_INT,
				0,
				m_material->GetAmountInstancedObject()
			);
			mesh->unbindVAO();
			glActiveTexture(GL_TEXTURE0);
		}
		m_VBO->Unbind();
	}
	void InstancedBuffer::PrepareInstacedObjects(Matrix4* m_model)
	{
		for (unsigned int i = 0; i < m_object.size(); i++)
		{
			Matrix4 model = m_object[i]->getTransform()->getModelMatrix();
			m_model[i] = model;
		}
	}
	void InstancedBuffer::CreateVBOBuffer(Matrix4* m_model)
	{
		m_VBO = createRef<VertexBufferObject>(&m_model[0], m_object.size() * sizeof(Matrix4), GL_STATIC_DRAW);
	}
	void InstancedBuffer::ConfigureInstancedAttributes()
	{
		for (unsigned int j = 0; j < m_meshs.size(); j++) {

			ref<VertexArrayObject> vao = m_meshs[j]->GetVAO();
			vao->Bind();
			// set attribute pointers for matrix (4 times vec4)
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)0);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(sizeof(Vector4)));
			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(2 * sizeof(Vector4)));
			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4), (void*)(3 * sizeof(Vector4)));

			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);

			vao->Unbind();
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