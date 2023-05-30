#include "Time.h"
namespace openge {
	double Time::time() const
	{
		return glfwGetTime();
	}

	double Time::deltaTime() const
	{
		return m_deltaTime;
	}

	void Time::updateDeltaTime()
	{
		auto currentTime = glfwGetTime();
		m_deltaTime = currentTime - m_previousTime;
		m_previousTime = currentTime;
	}
}
