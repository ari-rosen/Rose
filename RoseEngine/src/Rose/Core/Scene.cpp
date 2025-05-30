#include "Rose/Core/Scene.hpp"
#include "Rose/ComponentSystem/Component.hpp"
#include "Rose/ComponentSystem/System.hpp"
#include "Rose/Graphics/Renderer.hpp"
#include "Rose/ComponentSystem/SystemManager.hpp"
#include "Rose/Core/Application.hpp"

namespace Rose {

Scene::Scene() {
    m_CameraZoom = 1.0f;
    m_CameraPosition = {0.0f, 0.0f};

    m_ObjectManager = std::make_unique<ObjectManager>();
    m_ComponentManager = std::make_unique<ComponentManager>();
    m_SystemManager = std::make_unique<SystemManager>();
    
    registerComponent<ViewComponent>();
    registerComponent<TransformComponent>();
    registerComponent<SpriteComponent>();
    registerComponent<RigidBodyComponent>();
}

Scene::~Scene() {}

void Scene::setRenderer(std::shared_ptr<Renderer> renderer) {
    registerSystem<RenderSystem>(renderer);
}

void Scene::setCameraPosition(const glm::vec2 newPos) {
    m_CameraPosition = newPos;
}
void Scene::moveCamera(const glm::vec2 delta) {
    m_CameraPosition += delta;
}
void Scene::setCameraZoom(const float newZoom) {
    m_CameraZoom = newZoom;
}



GameObject Scene::createGameObject() {
    GameObject obj =  m_ObjectManager->createGameObject();
    m_SystemManager->onObjectCreation(obj);
    return obj;
}

TextureID Scene::createTexture(const std::filesystem::path &path, const TextureParameter &params) {
    return app->getRenderer()->createTexture(path, params);
}

TextureID Scene::createTexture(const std::filesystem::path &path) {
    return app->getRenderer()->createTexture(path, TextureParameter());
}

void Scene::destroyGameObject(GameObject obj) {
    m_ComponentManager->onObjectDeath(obj);
    m_SystemManager->onObjectDeath(obj);
    m_ObjectManager->destroyGameObject(obj);
}

TimerID Scene::createTimer(uint32_t milliseconds, const std::function<void()> &func, bool repeat) {
    return m_TimerManager.createTimer(milliseconds, func, repeat);
}

void Scene::startTimer(TimerID id) {
    m_TimerManager.startTimer(id);
}

void Scene::pauseTimer(TimerID id) {
    m_TimerManager.pauseTimer(id);
}

void Scene::deleteTimer(TimerID id) {
    m_TimerManager.deleteTimer(id);
}

void Scene::updateSystems(float DeltaTime) {
    m_TimerManager.onUpdate(DeltaTime);
    m_SystemManager->onUpdate(this, DeltaTime);
}

void Scene::onEvent(Event &e) {}

}
