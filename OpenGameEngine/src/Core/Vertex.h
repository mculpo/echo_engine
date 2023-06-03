#ifndef __VERTEX_H__
#define __VERTEX_H__
#include <Core/tspch.h>
namespace openge {
	class Vertex {
	private:
		Vector3 _pos;
		Vector3 _normal;
		Vector2 _tex;
	public:
		Vertex(){}
		Vertex(const Vector3 pos, const Vector3 normal, const Vector2 tex) \
		{
			_pos = pos;
			_normal = normal;
			_tex = tex;
		}
	};
}
#endif
