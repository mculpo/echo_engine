#include "Mesh.h"
namespace openge {

	Mesh::Mesh() {}

	Mesh::Mesh(std::uint64_t id, const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo)
		: Component(id), m_positions(meshData.positions), m_normals(meshData.normals), m_texCoords(meshData.texCoords), m_indices(indices),
		m_vbo(vbo), m_vao(vao), m_ebo(ebo) {}

	Mesh::Mesh(Entity* entity, std::uint64_t id, const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo)
		: Component(entity, id), m_positions(meshData.positions), m_normals(meshData.normals), m_texCoords(meshData.texCoords), m_indices(indices),
		m_vbo(vbo), m_vao(vao), m_ebo(ebo) {}

	Mesh::Mesh(const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo)
		: m_positions(meshData.positions), m_normals(meshData.normals), m_texCoords(meshData.texCoords), m_indices(indices),
		m_vbo(vbo), m_vao(vao), m_ebo(ebo){}

	Mesh::Mesh(Entity* entity, std::uint64_t id) : Component(entity, id)
	{
	}

	Mesh::~Mesh()
	{
		delete m_vao;
		delete m_ebo;
		delete m_vbo;
	}

	void Mesh::setup()
	{

		m_vao = new VertexArrayObject();
		m_vbo = new VertexBufferObject(m_vertices.data(), m_vertices.size() * sizeof(float), GL_STATIC_DRAW);
		//m_ebo = new ElementBufferObject(m_indices.data(), sizeof(m_indices), GL_STATIC_DRAW);

		m_vao->AddLayout(3, VP_FLOAT); // position
		m_vao->AddLayout(3, VP_FLOAT); // color
		m_vao->AddLayout(2, VP_FLOAT); // texture

		m_vao->runLayout();

		m_vbo->Unbind();
		m_vao->Unbind();
	}

	void Mesh::setMeshData(MeshData& meshData)
	{
		m_positions = meshData.positions;
		m_normals = meshData.normals;
		m_texCoords = meshData.texCoords;
	}

	void Mesh::setIndices(std::vector<unsigned int>& indices)
	{
		m_indices = indices;
	}

	void Mesh::setVertices(std::vector<float>& vertices)
	{
		m_vertices = vertices;
	}
	void Mesh::useVAO() const
	{
		m_vao->Bind();
	}
	void Mesh::useVBO() const
	{
		m_vbo->Bind();
	}
	void Mesh::useEBO() const
	{
		m_ebo->Bind();
	}
}