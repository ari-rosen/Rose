#include "Rose/Core/Application.hpp"

#include "Rose/Core/Core.hpp"

#include "Rose/Events/ApplicationEvent.hpp"
#include "Rose/Events/Event.hpp"

#include "Rose/Graphics/Renderer.hpp"

#include "GLFW/glfw3.h"

namespace Rose {

Application::Application() 
    : m_Running(true), m_Window(WindowAttributes()), m_Renderer(std::make_shared<Renderer>()) 
{
    m_Window.setEventCallbackFunction(std::bind(&Application::onEventCore, this, std::placeholders::_1));
    m_Renderer->init();
}

Application::Application(const char *title, uint32_t winWidth, uint32_t winHeight)
    : m_Running(true), m_Window(WindowAttributes(title, winWidth, winHeight)), m_Renderer(std::make_shared<Renderer>()) 
{
    m_Window.setEventCallbackFunction(std::bind(&Application::onEventCore, this, std::placeholders::_1));
    m_Renderer->init();
}

Application::~Application() {}

void Application::onEvent(Event &e) {}

void Application::onEventCore(Event &e) {
    onEvent(e);
    if (m_ActiveScene) {
        m_ActiveScene->onEvent(e);
    }
    EventDispatcher eventDispatcher(e);
    eventDispatcher.dispatch<WindowCloseEvent>(ROSE_BIND_EVENT_FUNC(Application::onWindowClose));
}
 
void Application::onWindowClose(WindowCloseEvent &e) {
    std::cout << "[ROSE]: Window Close Event Triggered" << std::endl;
    std::cout << "[ROSE]: Application Shutting Down" << std::endl; 
    m_Running = false;
}


void Application::setActiveScene(std::shared_ptr<Scene> scene) {
    m_ActiveScene = std::move(scene);
    m_ActiveScene->app = this;
    m_ActiveScene->setRenderer(m_Renderer);
    m_ActiveScene->onStart();
}
void Application::run() {
    while (m_Running) {
        m_Window.onUpdate();

        updateDeltaTime();
        
        if (m_ActiveScene) {
            m_ActiveScene->onUpdate(DeltaTime);
            m_ActiveScene->updateSystems(DeltaTime);
        }

        m_Renderer->renderScene(m_Window.getGLFWWindow(), m_ActiveScene->getCameraViewMatrix(), m_ActiveScene->getCameraZoom());

        m_Window.swapBuffers();
    } 

}

void Application::updateDeltaTime() {
    CurrentFrameTime = glfwGetTime();
    DeltaTime = CurrentFrameTime - LastFrameTime;
    LastFrameTime = CurrentFrameTime;
}

}
