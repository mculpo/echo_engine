#ifndef __TIME_H__
#define __TIME_H__
#include "singleton/Singleton.h"
#include <GLFW/glfw3.h>
// Classe Time que herda de Singleton<Time>
class Time : public Singleton<Time> {
public:
    double time() const;
    double deltaTime() const;
    void updateDeltaTime();
    Time() = default;
    ~Time() = default;
private:
    double m_deltaTime = 0.0;
    double m_previousTime = 0.0;
};

#endif // !__TIME_H__



