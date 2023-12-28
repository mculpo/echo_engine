#ifndef ECHO_VERTEX
#define ECHO_VERTEX
#include <core/core.h>
namespace echo {
	struct Vertex {
		Vector3 _pos;
		Vector3 _normal;
		Vector2 _tex;
		Vector3 _tangent;
		Vector3 _bitangent;
	};
}
#endif // !ECHO_VERTEX
