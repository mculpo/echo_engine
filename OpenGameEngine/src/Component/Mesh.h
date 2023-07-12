#ifndef __MESH_H__
#define __MESH_H__
#include <Core/tspch.h>
#include <Component/Component.h>
#include <Renderer/ElementBufferObject.h>
#include <Renderer/VertexBufferObject.h>
#include <Renderer/VertexArrayObject.h>
#include <Core/Vertex.h>
#include <Core/Vertex.h>
#include <Renderer/Texture.h>
#include <Component/Material.h>


namespace openge {
	class Mesh : public Component
	{
	public:
		Mesh() {};
		~Mesh() {};

		void setup();
		void disableVertexAttribArray();

		void setIndices(std::vector<unsigned int>& indices);
		void setVertices(std::vector<Vertex>& vertices);
		void setTextures(std::vector<ref<Texture>> textures);
		void addTexture(ref <Texture> texture, String name);
		void addTexture(ref <Texture> texture);

		void setVAO(ref<VertexArrayObject> vao);
		void setVBO(ref<VertexBufferObject> vbo);
		void setEBO(ref<ElementBufferObject> ebo);

		void bindTexture(ref<Material> material) const;
		void useVAO() const;
		void useVBO() const;
		void useEBO() const;
	private:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
		std::vector<ref<Texture>> m_textures;

		ref<VertexArrayObject> m_vao;
		ref<VertexBufferObject> m_vbo;
		ref<ElementBufferObject> m_ebo;
	};

}
#endif // !__MESH_H__





