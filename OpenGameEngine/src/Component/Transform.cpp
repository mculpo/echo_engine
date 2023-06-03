#include "Transform.h"
namespace openge {


	Transform::Transform(const glm::vec3 position = glm::vec3(0.0f),
		const glm::vec3 scale = glm::vec3(0.0f),
		const glm::quat rotation = glm::quat()) :  m_position(position), m_scale(scale), m_rotation(rotation) {}

	Transform::~Transform()
	{}

	Matrix4 Transform::getModelMatrix()
	{
		Matrix4 model = Matrix4(1.0f);
		model = glm::translate(model, m_position);
		model = glm::scale(model, m_scale);

		model = model * glm::mat4_cast(m_rotation);

		/*model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));*/
		return model;
	}

	Matrix3 Transform::getTransposeMatrix()
	{
		return glm::transpose(
			glm::inverse(
				Matrix3(getModelMatrix())
			)
		);
	}

	void Transform::scale(const glm::vec3 scale)
	{
		m_scale = scale;
	}

	void Transform::translate(const glm::vec3 translation)
	{
		m_position += translation;
	}

	void Transform::rotate(const glm::quat& angles)
	{
		m_rotation = angles * m_rotation;
	}

	void Transform::lookAt(const glm::vec3& target, float speed)
	{
		glm::vec3 direction = glm::normalize(target - m_position);
		/*
		* glm::quatLookAt:
		A função glm::quatLookAt é parte da biblioteca GLM (OpenGL Mathematics) e é usada para calcular uma rotação de quaternião com base em uma direção desejada. Ela recebe dois parâmetros: direction (direção) e up (vetor "para cima").

		A função calcula o quaternião que representa a rotação necessária para que o vetor de direção aponte para a frente (eixo -Z) e o vetor "para cima" seja alinhado com o vetor especificado por up. Essa função é frequentemente usada para orientar objetos em 3D para que eles "olhem para" um determinado alvo.

		A função glm::eulerAngles é usada para extrair os ângulos de Euler de um quaternion ou de uma matriz de rotação. Ela recebe como entrada um quaternion ou uma matriz de rotação e retorna um vetor de três componentes representando os ângulos de rotação nos eixos X, Y e Z.
		*/
		glm::quat targetRotation = glm::quatLookAt(direction, glm::vec3(0.0f, 1.0f, 0.0f)); // Calcula o quaternion desejado

		// Interpolar entre a rotação atual e a rotação desejada com base na velocidade de rotação
		m_rotation = glm::slerp(m_rotation, targetRotation, speed); // Interpolação de quaternions
	}

	Vector3 Transform::getPosition() const
	{
		return m_position;
	}

	Vector3 Transform::getScale() const
	{
		return m_scale;
	}

	Quaternion Transform::getRotation() const
	{
		return m_rotation;
	}

	std::string Transform::toString() const
	{
		std::string result;
		result += "Position: " + glm::to_string(m_position) + "\n";
		result += "Scale: " + glm::to_string(m_scale) + "\n";
		result += "Rotation: " + glm::to_string(m_rotation) + "\n";
		return result;
	}
}
