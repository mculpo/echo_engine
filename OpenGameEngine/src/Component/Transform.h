#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <Core/tspch.h>
#include <Component/Component.h>

namespace openge {
	class Component;
	class Transform : public Component
	{
	public:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::quat m_rotation;

		Transform(const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation);
		~Transform();
		glm::mat4 getModelMatrix();

		void translate(const glm::vec3 translation);
		void scale(const glm::vec3 scale);
		void rotate(const glm::quat& angles);
		void lookAt(const glm::vec3& target, float speed);

		std::string toString() const;
	};
}
#endif // !__TRANSFORM_H__





