#include "Camera.h"
namespace openge {
	Camera::Camera() :Component() {}

	Camera::~Camera() {}

	glm::mat4 Camera::getViewMatrix()
	{
		std::shared_ptr<Transform> transform = getEntity()->getComponent<Transform>();
		return glm::lookAt(transform->m_position, transform->m_position + m_front, m_up);
	}

	glm::mat4 openge::Camera::getProjectionMatrix()
	{

		if (m_type == CameraType::Perpective) {
			return glm::perspective(glm::radians(m_fov), m_aspectRatio, m_nearPlane, m_farPlane);
		}
		else {
			float halfWidth = m_aspectRatio * m_nearPlane;
			float halfHeight = m_nearPlane;
			return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, m_nearPlane, m_farPlane);
		}
	}

	void openge::Camera::setCameraType(const CameraType value)
	{
		m_type = value;
	}

	void openge::Camera::setFov(const float value)
	{
		m_fov = value;
	}

	void openge::Camera::setAspectRatio(const float value)
	{
		m_aspectRatio = value;
	}

	void openge::Camera::setNearPlane(const float value)
	{
		m_nearPlane = value;
	}

	void openge::Camera::setFarPlane(const float value)
	{
		m_farPlane = value;
	}

	void openge::Camera::setFront(const glm::vec3& front)
	{
		m_front = front;
	}

	void openge::Camera::setUp(const glm::vec3& up)
	{
		m_up = up;
	}

	CameraType openge::Camera::getCameraType() const
	{
		return m_type;
	}

	float openge::Camera::getFov() const
	{
		return m_fov;
	}

	float openge::Camera::getAspectRatio() const
	{
		return m_aspectRatio;
	}

	float openge::Camera::getNearPlane() const
	{
		return m_nearPlane;
	}

	float openge::Camera::getFarPlane() const
	{
		return m_farPlane;
	}

	glm::vec3 openge::Camera::getFront() const
	{
		return m_front;
	}

	glm::vec3 openge::Camera::getUp() const
	{
		return m_up;
	}
}
