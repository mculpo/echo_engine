#ifndef __MESH_H__
#define __MESH_H__
#include <Core/tspch.h>
#include <Component/Component.h>
#include <Renderer/ElementBufferObject.h>
#include <Renderer/VertexBufferObject.h>
#include <Renderer/VertexArrayObject.h>


namespace openge {
	struct MeshData {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
	};
	class Mesh : public Component
	{
	public:
		Mesh() {};
		~Mesh() {};

		void setup();

		void setMeshData(MeshData& meshData);
		void setIndices(std::vector<unsigned int>& indices);
		void setVertices(std::vector<float>& vertices);

		void setVAO(std::shared_ptr<VertexArrayObject> vao);
		void setVBO(std::shared_ptr<VertexBufferObject> vbo);
		void setEBO(std::shared_ptr<ElementBufferObject> ebo);

		void useVAO() const;
		void useVBO() const;
		void useEBO() const;
	private:
		std::vector<glm::vec3> m_positions;
		std::vector<glm::vec3> m_normals;
		std::vector<glm::vec2> m_texCoords;
		std::vector<unsigned int> m_indices;
		std::vector<float> m_vertices;

		std::shared_ptr<VertexArrayObject> m_vao;
		std::shared_ptr<VertexBufferObject> m_vbo;
		std::shared_ptr<ElementBufferObject> m_ebo;
	};

}
#endif // !__MESH_H__





