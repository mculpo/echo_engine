#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Component.h"
#include "../core/Time.h"
#include <string>
namespace openge {
	class Transform : public Component
	{
	public:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::quat m_rotation;

		Transform(Entity& entity, std::uint64_t id, const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation);
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





