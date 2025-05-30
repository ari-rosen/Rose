#pragma once

#include "Rose/Core/KeyCode.hpp"

#include <GLFW/glfw3.h>

namespace Rose {

class Input {
public:
    static bool isKeyDown(KeyCode key);
    static bool s_Keys[1024];
    static void Init();
    static void SetKeyState(KeyCode key, bool pressed);
    
};

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
