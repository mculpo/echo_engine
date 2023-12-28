#ifndef ECHO_MESH
#define ECHO_MESH
#include <core/core.h>
#include "gl/VertexArrayObject.hpp"
#include "gl/VertexBufferObject.hpp"
#include "gl/ElementBufferObject.hpp"
#include "Vertex.hpp"
namespace echo::mesh {
	struct Mesh {
		std::vector<unsigned int> mIndices;
		std::vector<Vertex> mVertices;
		std::vector<unsigned int> mIndexTextures;

		echo::gl::VertexArrayObject* mVAO;
		echo::gl::VertexBufferObject* mVAO;
		echo::gl::ElementBufferObject* mEBO;
	};
}
namespace echo::mesh {
#ifndef ECHO_MESH_CODE
#define ECHO_MESH_CODE

#endif //!ECHO_MESH_CODE

}
#endif // !ECHO_MESH
