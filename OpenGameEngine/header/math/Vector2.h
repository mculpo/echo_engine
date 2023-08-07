#ifndef __VECTOR2_H__
#define __VECTOR2_H__

namespace math {
	class Vector2
	{
	public:
		float x;
		float y;
		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(float _x, float _y) : x(_x), y(_y) {}
		~Vector2() {}
		Vector2 operator+(const Vector2& vec) {
			return Vector2(x + vec.x, y + vec.y);
		}
		Vector2 operator-(const Vector2& vec) {
			return Vector2(x - vec.x, y - vec.y);
		}
		Vector2 operator*(float scalar) {
			return Vector2(x * scalar, y * scalar);
		}
		Vector2 operator/(float scalar) {
			return Vector2(x / scalar, y / scalar);
		}
		Vector2 operator/(const Vector2& vec) {
			return Vector2(x / vec.x, y / vec.y);
		}
	};
}
#endif // !__VECTOR2_H__



