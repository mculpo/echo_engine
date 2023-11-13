#ifndef __MESH_H__
#define __MESH_H__
#include <core/core.h>
#include <core/Vertex.h>
#include <core/Vertex.h>

#include <component/Component.h>

#include <base/Texture2D.h>
#include <base/Material.h>

#include <gl/VertexArrayObject.h>
#include <gl/VertexBufferObject.h>
#include <gl/ElementBufferObject.h>

#include <manager/TextureManager.h>

namespace openge {
	class Mesh 
	{
	public:
		Mesh() {};
		Mesh(std::vector<unsigned int> indices, std::vector<Vertex> vertices, std::vector<unsigned int> textures);
		~Mesh() {};

		void setup();
		void disableVertexAttribArray();

		void setIndices(std::vector<unsigned int>& indices);
		void setVertices(std::vector<Vertex>& vertices);
		void setTextures(std::vector<unsigned int>& textures);
		//void addTexture(Texture texture, String name);
		void addTexture(unsigned int texture);

		void setVAO(ref<VertexArrayObject> vao);
		void setVBO(ref<VertexBufferObject> vbo);
		void setEBO(ref<ElementBufferObject> ebo);

		ref<VertexArrayObject> GetVAO();

		const std::vector<unsigned int>& GetIndices() const;
		const std::vector<Vertex>& GetVertices() const;
		const std::vector<unsigned int>& GetTextures() const;

		void bindTexture(ref<Material> material) const;
		void useVAO() const;
		void unbindVAO() const;
		void useVBO() const;
		void useEBO() const;
	private:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_index_textures;

		ref<VertexArrayObject> m_vao;
		ref<VertexBufferObject> m_vbo;
		ref<ElementBufferObject> m_ebo;
	};

}
#endif // !__MESH_H__





