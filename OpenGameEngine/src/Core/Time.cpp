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
	void Time::toStringFpsAndMs()
	{
		double currentTime = glfwGetTime();
		m_frameCount++;
		if (currentTime - m_lastTime >= 1.0) { // A cada segundo
			double fps = static_cast<double>(m_frameCount);
			double msPerFrame = 1000.0 / fps;
			std::cout << "FPS: " << fps << " - MS por quadro: " << msPerFrame << std::endl;
			m_frameCount = 0;
			m_lastTime = currentTime;
		}
	}
}
