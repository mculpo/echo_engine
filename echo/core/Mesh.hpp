#ifndef ECHO_MESH
#define ECHO_MESH
#include <core/core.h>
#include <gl/VertexArrayObject.hpp>
#include <gl/VertexBufferObject.hpp>
#include <gl/ElementBufferObject.hpp>
#include <Vertex.hpp>
#include <Shader.hpp>
#include <manager/TextureManager.h>
namespace echo::mesh {
	struct Mesh {
		std::vector<unsigned int> mIndices;
		std::vector<Vertex> mVertices;
		std::vector<unsigned int> mIndexTextures;

		echo::gl::VertexArrayObject* mVAO;
		echo::gl::VertexBufferObject* mVBO;
		echo::gl::ElementBufferObject* mEBO;
	};
}
namespace echo::mesh {
#ifndef ECHO_MESH_CODE
#define ECHO_MESH_CODE

	void create(Mesh* pMesh, std::vector<unsigned int> pIndices, std::vector<Vertex> pVertices, std::vector<unsigned int> pTextures) {

		pMesh->mIndices = pIndices;
		pMesh->mVertices = pVertices;
		pMesh->mIndexTextures = pTextures;

		echo::gl::VertexArrayObject vao;
		echo::gl::VertexBufferObject vbo;
		echo::gl::ElementBufferObject ebo;

		pMesh->mVAO = new echo::gl::VertexArrayObject();
		pMesh->mVBO = &vbo;
		pMesh->mEBO = &ebo;

		echo::gl::vao::create(pMesh->mVAO);
		echo::gl::vbo::create(pMesh->mVBO, pVertices.data(), pVertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
		echo::gl::ebo::create(pMesh->mEBO, pIndices.data(), pIndices.size() * sizeof(unsigned int), GL_STATIC_DRAW);

		echo::gl::vao::attributeDate(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
		echo::gl::vao::attributeDate(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, mNormal));
		echo::gl::vao::attributeDate(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, mTex));
		echo::gl::vao::attributeDate(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, mTangent));
		echo::gl::vao::attributeDate(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, mBitangent));

		echo::gl::vao::unbind();
		echo::gl::vbo::unbind();
	}

	void disableMeshVertexAttribArray() {
		echo::gl::vao::attributeDisable(0);
		echo::gl::vao::attributeDisable(1);
		echo::gl::vao::attributeDisable(2);
		echo::gl::vao::attributeDisable(3);
		echo::gl::vao::attributeDisable(4);
	}

	void cleanUp(Mesh* pMesh) {
		// Deletar as instâncias de objetos alocadas dinamicamente no heap
		delete pMesh->mVAO;
		delete pMesh->mVBO;
		delete pMesh->mEBO;
	}

	void bindTexture(Mesh* pMesh, Shader* pShader) {
		echo::shader::bindProgram
	}

#endif //!ECHO_MESH_CODE

}
#endif // !ECHO_MESH
