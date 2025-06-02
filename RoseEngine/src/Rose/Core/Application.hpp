#pragma once

#include "Rose/Core/Core.hpp"

#include "Rose/Core/Window.hpp"
#include "Rose/Core/Scene.hpp"
#include "Rose/Events/ApplicationEvent.hpp"
#include "Rose/Events/Event.hpp"

namespace Rose {

class Renderer;
class UIRenderer;

class ROSE_API Application {
public:
    Application();
    Application(const char *title, uint32_t winWidth, uint32_t winHeight);
    virtual ~Application();
    
    void onEventCore(Event &e);
    virtual void onEvent(Event &e);

    void onWindowClose(WindowCloseEvent &e); 

    void setActiveScene(std::shared_ptr<Scene> scene);

    void run();

    inline void setClearColor(const glm::vec4 color) { m_Window.setClearColor(color); }
    inline std::shared_ptr<Renderer> getRenderer() const { return m_Renderer; }
private:
    void updateDeltaTime();
private:
    Window m_Window;
    
    std::shared_ptr<Renderer> m_Renderer;
    std::shared_ptr<UIRenderer> m_UIRenderer;
    
    bool m_Running;

    float DeltaTime;
    float LastFrameTime = 0;
    float CurrentFrameTime;

protected:
    std::shared_ptr<Scene> m_ActiveScene;
};

} // namespace Rose
