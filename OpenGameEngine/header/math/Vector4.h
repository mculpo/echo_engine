#ifndef __VECTOR4_H__
#define __VECTOR4_H__
namespace math {
	class Vector4
	{
	public:
		float x, y, z, w;
		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		~Vector4(){}

		Vector4 operator+(const Vector4& vec) {
			return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}
		Vector4 operator-(const Vector4& vec) {
			return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}
		Vector4 operator*(float scale) {
			return Vector4(x * scale, y * scale, z * scale, w * scale);
		}
		Vector4 operator/(float scale) {
			return Vector4(x / scale, y / scale, z / scale, w / scale);
		}
		Vector4 operator/(const Vector4& vec) {
			return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
		}
	}
}
#endif // !__VECTOR4_H__

