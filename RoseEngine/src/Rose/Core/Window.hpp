#include "Rose/Core/Core.hpp"
#include "Rose/Events/Event.hpp"

#include <glm/glm.hpp>

class GLFWwindow;

namespace Rose {

struct ROSE_API WindowAttributes {
    const char *Title;
    uint32_t Width;
    uint32_t Height;

    WindowAttributes(const char *title = "Rose Engine", const uint32_t width = 1280, const uint32_t height = 720);
};

class ROSE_API Window {
public:
    Window(const WindowAttributes &winAttrib);
    ~Window();
    
    void onUpdate();
    void swapBuffers();
    void setEventCallbackFunction(const std::function<void(Event&)> &callback);

    inline void setClearColor(const glm::vec4 color) { m_ClearColor = color; }
    inline uint32_t getWidth() const { return m_WindowData.Width; }
    inline uint32_t getHeight() const { return m_WindowData.Height; }
    inline GLFWwindow * getGLFWWindow() const { return m_GLFWwindow; }
private:
    GLFWwindow *m_GLFWwindow;
    
    struct WindowData {
        const char *Title;
        uint32_t Width, Height;

        std::function<void(Event&)> EventCallbackFunction; 
    };

    WindowData m_WindowData;

    glm::vec4 m_ClearColor;
};

} // namespace Rose
