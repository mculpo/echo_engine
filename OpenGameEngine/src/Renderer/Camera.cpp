#include "Camera.h"
namespace openge {
	Camera::Camera()
	{
	}
	Camera::~Camera()
	{
	}
	glm::mat4 Camera::getViewMatrix()
	{
		ref<Transform> transform = getEntity()->getComponent<Transform>();
		return glm::lookAt(transform->getPosition(), transform->getPosition() + m_front, m_up);
	}

	glm::mat4 Camera::getProjectionMatrix()
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

	void Camera::setCameraType(const CameraType value)
	{
		m_type = value;
	}

	void Camera::setFov(const float value)
	{
		m_fov = value;
	}

	void Camera::setAspectRatio(const float value)
	{
		m_aspectRatio = value;
	}

	void Camera::setNearPlane(const float value)
	{
		m_nearPlane = value;
	}

	void Camera::setFarPlane(const float value)
	{
		m_farPlane = value;
	}

	void Camera::setFront(const glm::vec3& front)
	{
		m_front = front;
	}

	void Camera::setUp(const glm::vec3& up)
	{
		m_up = up;
	}

	void Camera::setWorldUp(const Vector3& up)
	{
		m_worldUp = up;
	}

	CameraType Camera::getCameraType() const
	{
		return m_type;
	}

	float Camera::getFov() const
	{
		return m_fov;
	}

	float Camera::getAspectRatio() const
	{
		return m_aspectRatio;
	}

	float Camera::getNearPlane() const
	{
		return m_nearPlane;
	}

	float Camera::getFarPlane() const
	{
		return m_farPlane;
	}

	glm::vec3 Camera::getFront() const
	{
		return m_front;
	}

	glm::vec3 Camera::getUp() const
	{
		return m_up;
	}
	Vector3 Camera::getWorldUp() const
	{
		return m_worldUp;
	}
}
