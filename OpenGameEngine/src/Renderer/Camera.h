#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <Core/tspch.h>
#include "Component/Component.h"
#include "Component/Transform.h"
#include "Entity/Entity.h"
namespace openge {
	class Transform;
	enum class CameraType {
		Perpective,
		Orthographic
	};

	class Camera : public Component
	{
	private:
		glm::vec3 m_front;
		glm::vec3 m_up;
		Vector3 m_worldUp;
		float m_fov;
		float m_aspectRatio;
		float m_nearPlane;
		float m_farPlane;
		CameraType m_type;
	public:
		Camera();
		~Camera();

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		void setCameraType(const CameraType value);
		void setFov(const float value);
		void setAspectRatio(const float value);
		void setNearPlane(const float value);
		void setFarPlane(const float value);
		void setFront(const glm::vec3& front);
		void setUp(const glm::vec3& up);
		void setWorldUp(const Vector3& up);

		CameraType getCameraType() const;
		float getFov()const;
		float getAspectRatio()const;
		float getNearPlane()const;
		float getFarPlane()const;
		glm::vec3 getFront()const;
		glm::vec3 getUp()const;
		Vector3 getWorldUp()const;
	};
}
#endif

