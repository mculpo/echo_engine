#include "Mesh.h"
namespace openge {
	void Mesh::setup()
	{
		setVAO(std::make_shared<VertexArrayObject>());
		setVBO(std::make_shared<VertexBufferObject>(m_vertices.data(), m_vertices.size() * sizeof(Vertex), GL_STATIC_DRAW));
		setEBO(std::make_shared<ElementBufferObject>(m_indices.data(), m_indices.size() * sizeof(unsigned int), GL_STATIC_DRAW));
		
		m_vao->AddLayout(3, VP_FLOAT); // aPos
		m_vao->AddLayout(3, VP_FLOAT); // aNormal
		m_vao->AddLayout(2, VP_FLOAT); // aTexCoords

		m_vao->runLayout();

		m_vbo->Unbind();
		m_vao->Unbind();
	}

	void Mesh::disableVertexAttribArray()
	{
		m_vao->runLayout();
	}

	void Mesh::setIndices(std::vector<unsigned int>& indices)
	{
		m_indices = indices;
	}

	void Mesh::setVertices(std::vector<Vertex>& vertices)
	{
		m_vertices = vertices;
	}

	void Mesh::setTextures(std::vector<ref<Texture>> textures)
	{
		m_textures = textures;
	}

	void Mesh::addTexture(ref<Texture> texture, String name)
	{
		texture->SetName(name);
		m_textures.push_back(texture);
	}

	void Mesh::addTexture(ref<Texture> texture)
	{
		m_textures.push_back(texture);
	}

	void Mesh::setVAO(ref<VertexArrayObject> vao)
	{
		m_vao = std::move(vao);
	}

	void Mesh::setVBO(ref<VertexBufferObject> vbo) 
	{
		m_vbo = std::move(vbo);
	}
	void Mesh::setEBO(ref<ElementBufferObject> ebo) 
	{
		m_ebo = std::move(ebo);
	}

	void Mesh::bindTexture(ref<Material> material) const
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); 
			
			String number;
			TextureType textureType = m_textures[i]->GetTextureType();
			if (textureType == TextureType::Diffuse)
				number = std::to_string(diffuseNr++);
			else if (textureType == TextureType::Specular)
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (textureType == TextureType::Normal)
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (textureType == TextureType::Height)
				number = std::to_string(heightNr++); // transfer unsigned int to string

			material->getShader()->setUniform1i(m_textures[i]->GetName(), i);
			glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetTexture());
		}
	}

	void Mesh::useVAO() const
	{
		m_vao.get()->Bind();
	}
	void Mesh::useVBO() const
	{
		m_vbo.get()->Bind();
	}
	void Mesh::useEBO() const
	{
		m_ebo.get()->Bind();
	}
}