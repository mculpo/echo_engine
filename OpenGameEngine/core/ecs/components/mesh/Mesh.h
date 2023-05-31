#ifndef __MESH_H__
#define __MESH_H__

#include <ecs/components/Component.h>
#include <glm/glm.hpp>
#include <ecs/system/renderer/ElementBufferObject.h>
#include <ecs/system/renderer/VertexBufferObject.h>
#include <ecs/system/renderer/VertexArrayObject.h>


namespace openge {
	struct MeshData {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
	};
	class Mesh : public Component
	{
	public:
		Mesh();
		Mesh(std::uint64_t id, const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo);
		Mesh(const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo);
		Mesh(Entity* entity, std::uint64_t id);
		Mesh(Entity* entity, std::uint64_t id, const MeshData& meshData, std::vector<unsigned int> indices, VertexArrayObject* vao, VertexBufferObject* vbo, ElementBufferObject* ebo);
		~Mesh();

		void setup();

		void setMeshData(MeshData& meshData);
		void setIndices(std::vector<unsigned int>& indices);
		void setVertices(std::vector<float>& vertices);
		void useVAO() const;
		void useVBO() const;
		void useEBO() const;
	private:
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_texCoords;
		std::vector<unsigned int> m_indices;
		std::vector<float> m_vertices;

		VertexArrayObject* m_vao;
		VertexBufferObject* m_vbo;
		ElementBufferObject* m_ebo;
	};

}
#endif // !__MESH_H__





