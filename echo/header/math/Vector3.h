#ifndef __VECTOR3_H__
#define __VECTOR3_H__
namespace math {
	class Vector3 {
	public:
		float x, y, z;
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
		~Vector3() {}
		Vector3 operator+(const Vector3& vec) {
			return Vector3(x + vec.x, y + vec.y, z + vec.z);
		}

		Vector3 operator-(const Vector3& vec) {
			return Vector3(x - vec.x, y - vec.y, z - vec.z);
		}

		Vector3 operator*(float scalar) {
			return Vector3(x * scalar, y * scalar, z * scalar);
		}
		Vector3 operator/(float scalar) {
			return Vector3(x / scalar, y / scalar, z / scalar);
		}

		Vector3 operator/(const Vector3& vec) {
			return Vector3(x / vec.x, y / vec.y, z / vec.z);
		}
	};
}
#endif // !__VECTOR3_H__

