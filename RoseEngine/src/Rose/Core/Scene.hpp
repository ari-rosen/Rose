#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/Core/Timer.hpp"
#include "Rose/ComponentSystem/ObjectManager.hpp"
#include "Rose/ComponentSystem/ComponentManager.hpp"
#include "Rose/ComponentSystem/SystemManager.hpp"
#include "Rose/Events/Event.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Rose {

using TextureID = uint32_t;

class Renderer;
class Application;
struct TextureParameter;

class ROSE_API Scene {
public:
    Scene();
    virtual ~Scene();

    GameObject createGameObject();
    TextureID createTexture(const std::filesystem::path &imagePath, const TextureParameter &params);
    TextureID createTexture(const std::filesystem::path &imagePath);

    void destroyGameObject(GameObject obj);
    void setRenderer(std::shared_ptr<Renderer> renderer);

    TimerID createTimer(uint32_t milliseconds, const std::function<void()> &func, bool repeat);
    void startTimer(TimerID id);
    void pauseTimer(TimerID id);
    void deleteTimer(TimerID id);

    inline glm::mat4 getCameraViewMatrix() const {return glm::translate(glm::mat4(1.0f), glm::vec3(-m_CameraPosition, 0.0f));};
    inline float getCameraZoom() const { return m_CameraZoom; };

    void setCameraPosition(const glm::vec2 newPos);
    void moveCamera(const glm::vec2 delta);
    void setCameraZoom(const float newZoom);

    template <typename T>
    void registerComponent() {
        m_ComponentManager->registerComponent<T>();
    }

    template <typename ...Args>
    void addComponents(GameObject obj) {
        m_ComponentManager->addComponents<Args...>(obj, m_ObjectManager->getFlagsArray());
    }

    template <typename T>
    void insertComponentData(GameObject obj, T component) {
        m_ComponentManager->insertComponentData<T>(obj, component);
    }

    template <typename T>
    void removeComponentData(GameObject obj) {
        m_ComponentManager->removeComponentData<T>(obj);
    }

    template <typename T>
    T& getComponent(GameObject obj) {
        return m_ComponentManager->getComponentData<T>(obj); 
    }

    template <typename T, typename... Args> 
    void registerSystem(Args&&... args) {
        m_SystemManager->registerSystem<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    void removeSystem() {
        m_SystemManager->removeSystem<T>();
    }

    void updateSystems(float DeltaTime);

    virtual void onStart() = 0;
    virtual void onUpdate(float DeltaTime) = 0;
    virtual void onEvent(Event &e);
public:
    Application *app;
private:
    TimerManager m_TimerManager;
    std::unique_ptr<ObjectManager> m_ObjectManager;
    std::unique_ptr<ComponentManager> m_ComponentManager;
    std::unique_ptr<SystemManager> m_SystemManager;

    float m_CameraZoom;
    glm::vec2 m_CameraPosition;
};

}
