#pragma once

#include "Rose/ComponentSystem/GameObject.hpp"
#include "Rose/Core/Core.hpp"
#include <glm/glm.hpp>

namespace Rose {

struct ROSE_API ViewComponent {
    bool Visable;
    uint32_t Layer;
};

struct ROSE_API TransformComponent {
    glm::vec2 Position;
    float Rotation;
    glm::vec2 Scale; 
};

struct ROSE_API SpriteComponent {
    uint32_t TextureID;
};

struct ROSE_API RigidBodyComponent {
    glm::vec2 Acceleration;
    glm::vec2 Velocity;
};

using ComponentFlag = uint16_t;

template <typename T>
void ROSE_API setFlag(ComponentFlags &flags, const std::unordered_map<std::string, ComponentFlag> &idMap) {
    ComponentFlag value = idMap.at(typeid(T).name());
    flags.set(value);
}

template<typename ...Args>
ComponentFlags ROSE_API createComponentFlags(const std::unordered_map<std::string, ComponentFlag> &idMap) {
    ComponentFlags flags;
    (setFlag<Args>(flags, idMap), ...);
    return flags;
}

} // namespace Component namespace Rose
