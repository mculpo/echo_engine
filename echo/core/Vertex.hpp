#ifndef ECHO_VERTEX
#define ECHO_VERTEX
#include <core/core.h>
namespace echo {
	struct Vertex {
		Vector3 mPos;
		Vector3 mNormal;
		Vector2 mTex;
		Vector3 mTangent;
		Vector3 mBitangent;
	};
}
#endif // !ECHO_VERTEX
