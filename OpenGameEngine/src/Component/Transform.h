#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <Core/tspch.h>
#include <Component/Component.h>

namespace openge {
	class Component;
	class Transform : public Component
	{
	private:
		Vector3 m_position;
		Vector3 m_scale;
		Quaternion m_rotation;
	public:
		
		Transform(const Vector3 position, const Vector3 scale, const Quaternion rotation);
		~Transform();
		Matrix4 getModelMatrix();
		Matrix3 getTransposeMatrix();

		void translate(const Vector3 translation);
		void scale(const Vector3 scale);
		void rotate(const Quaternion& angles);
		void lookAt(const Vector3& target, float speed);

		Vector3 getPosition() const;
		Vector3 getScale() const;
		Quaternion getRotation() const;

		std::string toString() const;
	};
}
#endif // !__TRANSFORM_H__





