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

	int Time::getTargetFps() const
	{
		return m_targetFps;
	}

	void Time::setTargetFps(int targetFps)
	{
		m_targetFps = targetFps;
	}

	void Time::updateDeltaTime()
	{
		auto currentTime = glfwGetTime();
		m_deltaTime = currentTime - m_previousTime;
		m_previousTime = currentTime;
	}
}
