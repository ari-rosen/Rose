#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/ComponentSystem/GameObject.hpp"


namespace Rose {

class ROSE_API ComponentArrayI {
public:
    virtual ~ComponentArrayI() = default;
    virtual void onObjectDeath(GameObject obj) = 0;
};

template<typename T>
class ROSE_API ComponentArray : public ComponentArrayI {
public:
    void insertComponentData(GameObject obj, T componentData) {
        m_ObjectToIndexMap[obj] = m_Size;
        m_IndexToObjectMap[m_Size] = obj;
        m_Array[m_Size] = componentData;
        ++m_Size;
    }
    void removeData(GameObject obj) {
        if (m_Size == 0) return;

        size_t objectIndex = m_ObjectToIndexMap.at(obj); 
        m_Array[objectIndex] = m_Array[m_Size - 1];
    
        GameObject objOfLastElement = m_IndexToObjectMap[m_Size - 1];
        m_ObjectToIndexMap[objOfLastElement] = objectIndex;
        m_IndexToObjectMap[objectIndex] = objOfLastElement;
    
        m_ObjectToIndexMap.erase(obj);
        m_IndexToObjectMap.erase(m_Size - 1);

        m_Size --;
    }
    T& getComponentData(GameObject obj) {
        return m_Array[obj];
    }
    void onObjectDeath(GameObject obj) override {
        if (m_ObjectToIndexMap.find(obj) != m_ObjectToIndexMap.end()) {
              removeData(obj);
        }
    };
private:
    std::array<T, MAX_OBJECTS> m_Array;
    std::unordered_map<GameObject, size_t> m_ObjectToIndexMap;
    std::unordered_map<size_t, GameObject> m_IndexToObjectMap;
    size_t m_Size;
};

};
