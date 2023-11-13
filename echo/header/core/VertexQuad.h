#ifndef __VERTEXQUAD_H__
#define __VERTEXQUAD_H__
#include <core/core.h>
namespace openge {
	class VertexQuad {
	private:
		Vector2 _pos;
		Vector2 _tex;
	public:
		VertexQuad() : _pos(Vector2(0)), _tex(Vector2(0)) { }
		VertexQuad(const Vector2& pos, const Vector2& tex) {
			_pos = pos;
			_tex = tex;
		}

		// Getters
		Vector2 getPos() const {
			return _pos;
		}


		Vector2 getTex() const {
			return _tex;
		}

		// Setters
		void setPos(const Vector2& pos) {
			_pos = pos;
		}

		void setTex(const Vector2& tex) {
			_tex = tex;
		}
	};
}
#endif
