#include "Rose/Core/Input.hpp"

namespace Rose {

bool Input::s_Keys[1024] = { false };

bool Input::isKeyDown(KeyCode key) {
    return s_Keys[key];
}

void Input::SetKeyState(KeyCode key, bool pressed) {
    s_Keys[key] = pressed;
}

} // namespace Rose

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Rose::KeyCode keyCode = static_cast<Rose::KeyCode>(key);
    if (action == GLFW_PRESS)
        Rose::Input::SetKeyState(keyCode, true);
    else if (action == GLFW_RELEASE)
        Rose::Input::SetKeyState(keyCode, false);
}
