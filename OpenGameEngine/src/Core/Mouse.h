#ifndef __MOUSE_H__
#define __MOUSE_H__
#include <GLFW/glfw3.h>
#include "Core/Singleton.h"
namespace openge {
    class Mouse : public Singleton<Mouse> {
    private:
        GLFWwindow* m_window;
        double m_lastX;
        double m_lastY;
        double m_currentX;
        double m_currentY;
        bool m_isMoving;

    public:
        Mouse() : m_window(nullptr), m_lastX(0.0), m_lastY(0.0), m_currentX(0.0), m_currentY(0.0), m_isMoving(false) {}

        void update() {
            m_lastX = m_currentX;
            m_lastY = m_currentY;

            double xpos, ypos;
            glfwGetCursorPos(m_window, &xpos, &ypos);

            m_currentX = xpos;
            m_currentY = ypos;

            m_isMoving = (m_lastX != m_currentX || m_lastY != m_currentY);
        }

        void setWindow(GLFWwindow* window) {
            m_window = window;
        }

        bool isMoving() const {
            return m_isMoving;
        }

        double getX() const {
            return m_currentX;
        }

        double getY() const {
            return m_currentY;
        }
    };
}
#endif // DEBUG
