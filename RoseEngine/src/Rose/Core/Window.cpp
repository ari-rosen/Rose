#include "Rose/Core/Window.hpp"
#include "Rose/Events/KeyEvent.hpp"
#include "Rose/Events/MouseEvent.hpp"
#include "Rose/Events/ApplicationEvent.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Rose {

static uint8_t s_GLFWWindowCount = 0;

WindowAttributes::WindowAttributes(const char *title, const uint32_t width, const uint32_t height)
    : Title(title), Width(width), Height(height) {}

Window::Window(const WindowAttributes &winAttrib) 
    : m_ClearColor({0.2, 0.2, 0.2, 1.0})
{
    m_WindowData.Title = winAttrib.Title;
    m_WindowData.Height = winAttrib.Height;
    m_WindowData.Width = winAttrib.Width;

    if (s_GLFWWindowCount == 0) {
        if (!glfwInit()) {
            std::cout << "[ROSE]: ERROR: Failed to Initialize GLFW" << std::endl;
        }
    }
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

#ifdef ROSE_PLATFORM_MACOS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    
    m_GLFWwindow = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title, nullptr, nullptr);
    
    std::cout << "[ROSE]: Created Window '" << m_WindowData.Title << "'" << std::endl;
    
    if (!m_GLFWwindow) std::cout << "[ROSE]: ERROR: Failed to create window" << std::endl;
    s_GLFWWindowCount++;

    glfwSetWindowUserPointer(m_GLFWwindow, &m_WindowData);

    glfwMakeContextCurrent(m_GLFWwindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "[ROSE]: ERROR: Failed to Initialize OpenGL" << std::endl;
    } else {
        std::cout << "[ROSE]: OpenGL initialized: Version " << glGetString(GL_VERSION) << std::endl;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        
        WindowData &windowData = *(WindowData*)glfwGetWindowUserPointer(window); 
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            KeyPressedEvent event(key, (action == GLFW_REPEAT) ? 1 : 0);
            windowData.EventCallbackFunction(event);
        } else if (action == GLFW_RELEASE) {
            KeyReleasedEvent event(key);
            windowData.EventCallbackFunction(event);
        }
    });
    glfwSetWindowCloseCallback(m_GLFWwindow, [](GLFWwindow *window) {
        WindowData &windowData = *(WindowData*)glfwGetWindowUserPointer(window); 
        
        WindowCloseEvent event;
        windowData.EventCallbackFunction(event);
    });
    glfwSetCursorPosCallback(m_GLFWwindow, [](GLFWwindow *window, double x, double y) {
        WindowData &windowData = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event(x, y);
        windowData.EventCallbackFunction(event);
    });
    glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &windowData = *(WindowData*)glfwGetWindowUserPointer(window);
        
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            MouseButtonPressedEvent event(button, (action == GLFW_REPEAT) ? 1 : 0, 0);
            windowData.EventCallbackFunction(event);
        }
    });
}

Window::~Window() {
	glfwDestroyWindow(m_GLFWwindow);
	--s_GLFWWindowCount;

    if (s_GLFWWindowCount == 0)
	{
		glfwTerminate();
	}
}

void Window::onUpdate() {
    glfwPollEvents();

    glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_GLFWwindow);
}

void Window::setEventCallbackFunction(const std::function<void(Event&)> &callback) {
    m_WindowData.EventCallbackFunction = callback;
}

} // namespace Rose
