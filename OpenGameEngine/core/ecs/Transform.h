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
	class Transform : Component<Transform>
	{
	public:
		glm::vec3 m_position;
		glm::vec3 m_scale;
		glm::quat m_rotation;

		Transform(const glm::vec3 position, const glm::vec3 scale, const glm::quat rotation);
		~Transform();
		glm::mat4 getModelMatrix();

		Transform& operator=(const Transform& value);
		Transform operator-();
		Transform operator/(float scalar)const;
		Transform operator*(float scalar)const;
		Transform& operator/(const Transform& value)const;
		Transform& operator*(const Transform& value)const;

		void translate(const glm::vec3 translation);
		void rotate(const glm::quat& angles);
		void lookAt(const glm::vec3& target, float speed);

		std::string toString() const;

	private:
		
		float m_accumulatedAngle;  // Ângulo de rotação acumulado
	};
}
#endif // !__TRANSFORM_H__





