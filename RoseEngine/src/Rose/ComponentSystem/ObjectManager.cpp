#include "Rose/ComponentSystem/ObjectManager.hpp"

namespace Rose {

ObjectManager::ObjectManager() {
    for (GameObject obj = 0; obj < MAX_OBJECTS; obj++) {
       m_AvailibleObjects.push(obj); 
    }
}

GameObject ObjectManager::createGameObject() {
    GameObject newObj = m_AvailibleObjects.front();
    m_AvailibleObjects.pop();
    m_LivingObjectCount++;
    return newObj;
}

void ObjectManager::destroyGameObject(GameObject obj) {
    m_Flags[obj].reset();
    m_LivingObjectCount--;
    m_AvailibleObjects.push(obj);
}


} // namespace Rose
