#ifndef __TIME_H__
#define __TIME_H__
#include <Core/tspch.h>
#include "Core/Singleton.h"
#include <GLFW/glfw3.h>
namespace openge {
    // Classe Time que herda de Singleton<Time>
    class Time : public Singleton<Time> {
    public:
        double time() const;
        double deltaTime() const;

        void updateDeltaTime();
        void toStringFpsAndMs();
    
        Time() = default;
        ~Time() = default;
    private:
        double m_deltaTime = 0.0;
        double m_previousTime = 0.0;
        double m_currentTime = 0.0;
        double m_lastTime = 0.0;
        int m_frameCount = 0;
    };
}
#endif // !__TIME_H__



