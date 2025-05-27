#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/ComponentSystem/GameObject.hpp"
#include "Rose/ComponentSystem/System.hpp"

namespace Rose {

class Scene;

class ROSE_API SystemManager {
public:
    SystemManager();

    template <typename T, typename... Args>
    void registerSystem(Args&&... args) {
        std::string systemName = typeid(T).name();

        auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
        m_SystemMap.emplace(systemName, std::static_pointer_cast<System>(ptr));
    }
    
    template <typename T>
    void removeSystem() {
        std::string systemName = typeid(T).name();
        if (m_SystemMap.find(systemName) != m_SystemMap.end()) {
            m_SystemMap.erase(systemName);
        }
    }

    void onUpdate(Scene *scene, float DeltaTime);

    void onObjectCreation(GameObject obj);

    void onObjectDeath(GameObject obj);

private:
    std::set<GameObject> m_ObjectSet{};
    std::unordered_map<std::string, std::shared_ptr<System>> m_SystemMap{};
};

} // namespace Rose
