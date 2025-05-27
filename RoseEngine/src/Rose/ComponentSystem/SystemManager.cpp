#include "Rose/ComponentSystem/SystemManager.hpp"
#include "Rose/ComponentSystem/System.hpp"

namespace Rose {

SystemManager::SystemManager() {
}

void SystemManager::onUpdate(Scene *scene, float DeltaTime) {
    for (auto const &pair : m_SystemMap) {
        pair.second->onUpdate(m_ObjectSet, scene, DeltaTime);
    }
}

void SystemManager::onObjectCreation(GameObject obj) {
    m_ObjectSet.insert(obj);
}

void SystemManager::onObjectDeath(GameObject obj) {
    m_ObjectSet.erase(obj);
}

}
