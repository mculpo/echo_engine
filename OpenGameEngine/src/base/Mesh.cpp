#include <base/Mesh.h>

namespace openge {
	Mesh::Mesh(std::vector<unsigned int> indices, std::vector<Vertex> vertices, std::vector<unsigned int> textures) :
		m_indices(indices), m_vertices(vertices), m_index_textures(textures)
	{
		setup();
	}
	void Mesh::setup()
	{
		setVAO(std::make_shared<VertexArrayObject>());
		setVBO(std::make_shared<VertexBufferObject>(m_vertices.data(), m_vertices.size() * sizeof(Vertex), GL_STATIC_DRAW));
		setEBO(std::make_shared<ElementBufferObject>(m_indices.data(), m_indices.size() * sizeof(unsigned int), GL_STATIC_DRAW));
		
		m_vao->AddLayout(3, VP_FLOAT); // aPos
		m_vao->AddLayout(3, VP_FLOAT); // aNormal
		m_vao->AddLayout(2, VP_FLOAT); // aTexCoords

		m_vao->AddLayout(3, VP_FLOAT); // aTangent
		m_vao->AddLayout(3, VP_FLOAT); // aBitangent

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

	void Mesh::setTextures(std::vector<unsigned int>& textures)
	{
		m_index_textures = textures;
	}

	void Mesh::addTexture(unsigned int texture)
	{
		m_index_textures.push_back(texture);
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

	const std::vector<unsigned int>& Mesh::GetIndices() const {
		return m_indices;
	}

	// Implementação do método GetVertices()
	const std::vector<Vertex>& Mesh::GetVertices() const {
		return m_vertices;
	}

	// Implementação do método GetTextures()
	const std::vector<unsigned int>& Mesh::GetTextures() const {
		return m_index_textures;
	}

	void Mesh::bindTexture(ref<Material> material) const
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < m_index_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); 
			String number;
			ref<Texture> texture = TextureManager::getInstance().getTextureByIndex(m_index_textures[i]);
			TextureType textureType = texture->GetTextureType();
			if (textureType == TextureType::Diffuse)
				number = std::to_string(diffuseNr++);
			else if (textureType == TextureType::Specular)
				number = std::to_string(specularNr++); // transfer unsigned int to string
			else if (textureType == TextureType::Normal)
				number = std::to_string(normalNr++); // transfer unsigned int to string
			else if (textureType == TextureType::Height)
				number = std::to_string(heightNr++); // transfer unsigned int to string

			material->getShader()->setUniform1i(texture->GetName(), i);
			glBindTexture(GL_TEXTURE_2D, texture->GetTexture());
		}
	}

	void Mesh::useVAO() const
	{
		m_vao->Bind();
	}
	void Mesh::unbindVAO() const
	{
		m_vao->Unbind();
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