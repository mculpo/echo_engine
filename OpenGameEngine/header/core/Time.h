#ifndef __TIME_H__
#define __TIME_H__
#include <core/core.h>
#include "core/Singleton.h"
namespace openge {
    class Time {
    public:
        static double time() {
            return glfwGetTime();
        }
        static double deltaTime() {
            return m_deltaTime;
        }

        static void updateDeltaTime() {
            auto currentTime = glfwGetTime();
            m_deltaTime = currentTime - m_previousTime;
            m_previousTime = currentTime;
        }

        static void toStringFpsAndMs() {
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
    
    private:
        static double m_deltaTime;
        static double m_previousTime;
        static double m_currentTime;
        static double m_lastTime;
        static int m_frameCount;
    };

    double  Time::m_deltaTime = 0.0;
    double  Time::m_previousTime = 0.0;
    double  Time::m_currentTime = 0.0;
    double  Time::m_lastTime = 0.0;
    int     Time::m_frameCount = 0;
}
#endif // !__TIME_H__



