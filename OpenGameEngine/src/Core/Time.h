#ifndef __TIME_H__
#define __TIME_H__
#include "Core/Singleton.h"
#include <GLFW/glfw3.h>
namespace openge {
    // Classe Time que herda de Singleton<Time>
    class Time : public Singleton<Time> {
    public:
        double time() const;
        double deltaTime() const;
        int getTargetFps() const;

        void setTargetFps(int targetFps);

        void updateDeltaTime();
        Time() = default;
        ~Time() = default;
    private:
        double m_deltaTime = 0.0;
        double m_previousTime = 0.0;
        int m_targetFps = 60;
    };
}
#endif // !__TIME_H__



