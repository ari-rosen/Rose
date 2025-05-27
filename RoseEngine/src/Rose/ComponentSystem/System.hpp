#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/ComponentSystem/GameObject.hpp"

namespace Rose {

class Scene;

class ROSE_API System {
public:
    virtual void onUpdate(std::set<GameObject> &objects, Scene *scene, float DeltaTime) = 0;
    virtual ~System() = default;
};

} // namespace Rose
