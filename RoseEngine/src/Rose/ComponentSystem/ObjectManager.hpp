#pragma once

#include "Rose/ComponentSystem/GameObject.hpp"
#include "Rose/Core/Core.hpp"

namespace Rose {

class ROSE_API ObjectManager {
public:
    ObjectManager();

    GameObject createGameObject();
    ComponentFlags getComponentFlags(GameObject obj);
    void destroyGameObject(GameObject obj);

    inline std::array<ComponentFlags, MAX_OBJECTS>& getFlagsArray() { return m_Flags; }
private:
    std::queue<GameObject> m_AvailibleObjects;
    std::array<ComponentFlags, MAX_OBJECTS> m_Flags{};

    uint32_t m_LivingObjectCount;
};

} // namespace Rose
