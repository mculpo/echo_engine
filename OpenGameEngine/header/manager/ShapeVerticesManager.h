#ifndef __SHAPEVERTICESMANAGER_H__
#define __SHAPEVERTICESMANAGER_H__
#include <core/core.h>
#include <core/Vertex.h>
#include <core/Singleton.h>
#include <core/VertexQuad.h>

namespace openge {
	class ShapeVerticesManager: public Singleton<ShapeVerticesManager> {
	public:
		ShapeVerticesManager() {
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0.0f, 0.0f)));

			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, 0.0f, 1.0f), Vector2(0.0f, 0.0f)));

			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)));

			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector2(1.0f, 0.0f)));

			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, -0.5f, 0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, 0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, -0.5f, -0.5f), Vector3(0.0f, -1.0f, 0.0f), Vector2(0.0f, 1.0f)));

			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, 0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f)));
			cubeVertices.push_back(Vertex(Vector3(-0.5f, 0.5f, -0.5f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)));

			// Plane
			planeVertices.push_back(Vertex(Vector3(0.0f, 0.5f,  0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector2(0.0f, 1.0f)));
			planeVertices.push_back(Vertex(Vector3(0.0f, -0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), Vector2(0.0f, 0.0f)));
			planeVertices.push_back(Vertex(Vector3(1.0f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f)));
			planeVertices.push_back(Vertex(Vector3(0.0f, 0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(0.0f, 1.0f)));
			planeVertices.push_back(Vertex(Vector3(1.0f, -0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 0.0f)));
			planeVertices.push_back(Vertex(Vector3(1.0f, 0.5f, 0.0f), Vector3(1.0f, 1.0f, 0.0f), Vector2(1.0f, 1.0f)));

			// Plane
			quadVertices.push_back(VertexQuad(Vector2(-1.0f, 1.0f), Vector2(0.0f, 1.0f)));
			quadVertices.push_back(VertexQuad(Vector2(-1.0f, -1.0f), Vector2(0.0f, 0.0f)));
			quadVertices.push_back(VertexQuad(Vector2(1.0f, -1.0f), Vector2(1.0f, 0.0f)));
			quadVertices.push_back(VertexQuad(Vector2(-1.0f, 1.0f), Vector2(0.0f, 1.0f)));
			quadVertices.push_back(VertexQuad(Vector2(1.0f, -1.0f), Vector2(1.0f, 0.0f)));
			quadVertices.push_back(VertexQuad(Vector2(1.0f, 1.0f), Vector2(1.0f, 1.0f)));

			// Skybox
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));

			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));

			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));

			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));

			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, 1.0f, -1.0f));

			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, -1.0f));
			skyboxVertices.push_back(Vector3(-1.0f, -1.0f, 1.0f));
			skyboxVertices.push_back(Vector3(1.0f, -1.0f, 1.0f));
		}

		std::vector<Vertex>& getCubeVertices() {
			return cubeVertices;
		}

		std::vector<Vertex>& getPlaneVertices() {
			return planeVertices;
		}

		std::vector<VertexQuad>& getQuadVertices() {
			return quadVertices;
		}

		std::vector<Vector3>& getSkyboxVertices() {
			return skyboxVertices;
		}

	private:
		std::vector<Vertex> cubeVertices;
		std::vector<Vertex> planeVertices;
		std::vector<VertexQuad> quadVertices;
		std::vector<Vector3> skyboxVertices;
	};
}

#endif // !__SHAPEVERTICESMANAGER_H__

