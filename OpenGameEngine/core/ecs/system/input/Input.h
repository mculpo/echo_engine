#include <GLFW/glfw3.h>

#include <GLFW/glfw3.h>

// Teclas de função
#define KEYCODE_SPACE           GLFW_KEY_SPACE
#define KEYCODE_APOSTROPHE      GLFW_KEY_APOSTROPHE
#define KEYCODE_COMMA           GLFW_KEY_COMMA
#define KEYCODE_MINUS           GLFW_KEY_MINUS
#define KEYCODE_PERIOD          GLFW_KEY_PERIOD
#define KEYCODE_SLASH           GLFW_KEY_SLASH
#define KEYCODE_0               GLFW_KEY_0
#define KEYCODE_1               GLFW_KEY_1
#define KEYCODE_2               GLFW_KEY_2
#define KEYCODE_3               GLFW_KEY_3
#define KEYCODE_4               GLFW_KEY_4
#define KEYCODE_5               GLFW_KEY_5
#define KEYCODE_6               GLFW_KEY_6
#define KEYCODE_7               GLFW_KEY_7
#define KEYCODE_8               GLFW_KEY_8
#define KEYCODE_9               GLFW_KEY_9
#define KEYCODE_SEMICOLON       GLFW_KEY_SEMICOLON
#define KEYCODE_EQUAL           GLFW_KEY_EQUAL
#define KEYCODE_A               GLFW_KEY_A
#define KEYCODE_B               GLFW_KEY_B
#define KEYCODE_C               GLFW_KEY_C
#define KEYCODE_D               GLFW_KEY_D
#define KEYCODE_E               GLFW_KEY_E
#define KEYCODE_F               GLFW_KEY_F
#define KEYCODE_G               GLFW_KEY_G
#define KEYCODE_H               GLFW_KEY_H
#define KEYCODE_I               GLFW_KEY_I
#define KEYCODE_J               GLFW_KEY_J
#define KEYCODE_K               GLFW_KEY_K
#define KEYCODE_L               GLFW_KEY_L
#define KEYCODE_M               GLFW_KEY_M
#define KEYCODE_N               GLFW_KEY_N
#define KEYCODE_O               GLFW_KEY_O
#define KEYCODE_P               GLFW_KEY_P
#define KEYCODE_Q               GLFW_KEY_Q
#define KEYCODE_R               GLFW_KEY_R
#define KEYCODE_S               GLFW_KEY_S
#define KEYCODE_T               GLFW_KEY_T
#define KEYCODE_U               GLFW_KEY_U
#define KEYCODE_V               GLFW_KEY_V
#define KEYCODE_W               GLFW_KEY_W
#define KEYCODE_X               GLFW_KEY_X
#define KEYCODE_Y               GLFW_KEY_Y
#define KEYCODE_Z               GLFW_KEY_Z
#define KEYCODE_LEFT_BRACKET    GLFW_KEY_LEFT_BRACKET
#define KEYCODE_BACKSLASH       GLFW_KEY_BACKSLASH
#define KEYCODE_RIGHT_BRACKET   GLFW_KEY_RIGHT_BRACKET
#define KEYCODE_GRAVE_ACCENT    GLFW_KEY_GRAVE_ACCENT
#define KEYCODE_WORLD_1         GLFW_KEY_WORLD_1
#define KEYCODE_WORLD_2         GLFW_KEY_WORLD_2

// Setas direcionais
#define KEYCODE_ARROW_UP        GLFW_KEY_UP
#define KEYCODE_ARROW_DOWN      GLFW_KEY_DOWN
#define KEYCODE_ARROW_LEFT      GLFW_KEY_LEFT
#define KEYCODE_ARROW_RIGHT     GLFW_KEY_RIGHT

// Teclas de modificação
#define KEYCODE_LEFT_SHIFT      GLFW_KEY_LEFT_SHIFT
#define KEYCODE_LEFT_CONTROL    GLFW_KEY_LEFT_CONTROL
#define KEYCODE_LEFT_ALT        GLFW_KEY_LEFT_ALT
#define KEYCODE_LEFT_SUPER      GLFW_KEY_LEFT_SUPER
#define KEYCODE_RIGHT_SHIFT     GLFW_KEY_RIGHT_SHIFT
#define KEYCODE_RIGHT_CONTROL   GLFW_KEY_RIGHT_CONTROL
#define KEYCODE_RIGHT_ALT       GLFW_KEY_RIGHT_ALT
#define KEYCODE_RIGHT_SUPER     GLFW_KEY_RIGHT_SUPER
#define KEYCODE_MENU            GLFW_KEY_MENU

// Teclado numérico
#define KEYCODE_KP_0            GLFW_KEY_KP_0
#define KEYCODE_KP_1            GLFW_KEY_KP_1
#define KEYCODE_KP_2            GLFW_KEY_KP_2
#define KEYCODE_KP_3            GLFW_KEY_KP_3
#define KEYCODE_KP_4            GLFW_KEY_KP_4
#define KEYCODE_KP_5            GLFW_KEY_KP_5
#define KEYCODE_KP_6            GLFW_KEY_KP_6
#define KEYCODE_KP_7            GLFW_KEY_KP_7
#define KEYCODE_KP_8            GLFW_KEY_KP_8
#define KEYCODE_KP_9            GLFW_KEY_KP_9
#define KEYCODE_KP_DECIMAL      GLFW_KEY_KP_DECIMAL
#define KEYCODE_KP_DIVIDE       GLFW_KEY_KP_DIVIDE
#define KEYCODE_KP_MULTIPLY     GLFW_KEY_KP_MULTIPLY
#define KEYCODE_KP_SUBTRACT     GLFW_KEY_KP_SUBTRACT
#define KEYCODE_KP_ADD          GLFW_KEY_KP_ADD
#define KEYCODE_KP_ENTER        GLFW_KEY_KP_ENTER
#define KEYCODE_KP_EQUAL        GLFW_KEY_KP_EQUAL

// Outras teclas
#define KEYCODE_BACKSPACE       GLFW_KEY_BACKSPACE
#define KEYCODE_TAB             GLFW_KEY_TAB
#define KEYCODE_ENTER           GLFW_KEY_ENTER
#define KEYCODE_CAPS_LOCK       GLFW_KEY_CAPS_LOCK
#define KEYCODE_NUM_LOCK        GLFW_KEY_NUM_LOCK
#define KEYCODE_PRINT_SCREEN    GLFW_KEY_PRINT_SCREEN
#define KEYCODE_SCROLL_LOCK     GLFW_KEY_SCROLL_LOCK
#define KEYCODE_PAUSE           GLFW_KEY_PAUSE
#define KEYCODE_DELETE          GLFW_KEY_DELETE
#define KEYCODE_INSERT          GLFW_KEY_INSERT
#define KEYCODE_HOME            GLFW_KEY_HOME
#define KEYCODE_END             GLFW_KEY_END
#define KEYCODE_PAGE_UP         GLFW_KEY_PAGE_UP
#define KEYCODE_PAGE_DOWN       GLFW_KEY_PAGE_DOWN
#define KEYCODE_ESCAPE          GLFW_KEY_ESCAPE
#define KEYCODE_MENU            GLFW_KEY_MENU

// Botões do mouse
#define MOUSE_BUTTON_1          GLFW_MOUSE_BUTTON_1
#define MOUSE_BUTTON_2          GLFW_MOUSE_BUTTON_2
#define MOUSE_BUTTON_3          GLFW_MOUSE_BUTTON_3
#define MOUSE_BUTTON_4          GLFW_MOUSE_BUTTON_4
#define MOUSE_BUTTON_5          GLFW_MOUSE_BUTTON_5
#define MOUSE_BUTTON_6          GLFW_MOUSE_BUTTON_6
#define MOUSE_BUTTON_7          GLFW_MOUSE_BUTTON_7
#define MOUSE_BUTTON_8          GLFW_MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT       GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_BUTTON_RIGHT      GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_BUTTON_MIDDLE     GLFW_MOUSE_BUTTON_MIDDLE

namespace openge {
    class Input {
    public:
        static bool IsKeyPressed(int key) {
            GLFWwindow* window = glfwGetCurrentContext();
            int state = glfwGetKey(window, key);
            return state == GLFW_PRESS;
        }

        static bool IsKeyReleased(int key) {
            GLFWwindow* window = glfwGetCurrentContext();
            int state = glfwGetKey(window, key);
            return state == GLFW_RELEASE;
        }

        static bool IsKeyHeld(int key) {
            GLFWwindow* window = glfwGetCurrentContext();
            int state = glfwGetKey(window, key);
            return state == GLFW_PRESS || state == GLFW_REPEAT;
        }
    };
}

