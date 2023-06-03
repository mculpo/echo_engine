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
		
		Transform(const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation);
		~Transform();
		Matrix4 getModelMatrix();
		Matrix3 getTransposeMatrix();

		void translate(const glm::vec3 translation);
		void scale(const glm::vec3 scale);
		void rotate(const glm::quat& angles);
		void lookAt(const glm::vec3& target, float speed);

		Vector3 getPosition() const;
		Vector3 getScale() const;
		Quaternion getRotation() const;

		std::string toString() const;
	};
}
#endif // !__TRANSFORM_H__





