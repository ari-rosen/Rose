#pragma once

#include "Rose/ComponentSystem/Component.hpp"
#include "Rose/Core/Core.hpp"
#include "Rose/ComponentSystem/ComponentArray.hpp"

namespace Rose {

class ROSE_API ComponentManager {
public:
    template <typename T>
    void registerComponent() {
        m_ComponetIdMap.insert({typeid(T).name(), nextAvaliableComponentFlag++});
        m_ComponetArrayMap.insert({typeid(T).name(), std::make_shared<ComponentArray<T>>()});
    }

    template <typename ...Args>
    void addComponents(GameObject obj, std::array<ComponentFlags, MAX_OBJECTS> &flagsArray) {
        flagsArray[obj] = createComponentFlags<Args...>(m_ComponetIdMap);
    }

    template <typename T>
    void insertComponentData(GameObject obj, T component) {
        getComponentArray<T>()->insertComponentData(obj, component);                
    }

    template <typename T>
    void removeComponentData(GameObject obj) {
        getComponentArray<T>()->removeData(obj);
    }

    template <typename T>
    T& getComponentData(GameObject obj) {
        return getComponentArray<T>()->getComponentData(obj);
    }
    
    void onObjectDeath(GameObject obj) {
        for (auto &pair : m_ComponetArrayMap) {
            auto &componentArray = pair.second;
            componentArray->onObjectDeath(obj);
        } 
    }

    std::unordered_map<std::string, ComponentFlag> getComponentIDMap() {
        return m_ComponetIdMap;
    }
private:
    ComponentFlag nextAvaliableComponentFlag = 0;
    std::unordered_map<std::string, ComponentFlag> m_ComponetIdMap{};
    std::unordered_map<std::string, std::shared_ptr<ComponentArrayI>> m_ComponetArrayMap{}; 
private:
    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        std::string index = typeid(T).name();
        return std::static_pointer_cast<ComponentArray<T>>(m_ComponetArrayMap[index]);
    }
};

} // namespace Rose
