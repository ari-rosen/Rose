#pragma once
#include "Rose/Core/Core.hpp"
#include "Rose/Events/Event.hpp"

namespace Rose {

class ROSE_API WindowResizeEvent : public Event {
public:
    WindowResizeEvent(uint32_t width, uint32_t height);
    
    inline uint32_t getWidth() const { return m_Width; }
    inline uint32_t getHeight() const { return m_Height; }

    static EventType getStaticType();
    EventType getEventType() const override;
    const char *getName() const override;
    int8_t getCatagoryFlags() const override;

private:
    uint32_t m_Width;
    uint32_t m_Height;
};

class ROSE_API WindowCloseEvent : public Event {
public:
    WindowCloseEvent() {};
    
    static EventType getStaticType();
    EventType getEventType() const override;
    const char *getName() const override;
    int8_t getCatagoryFlags() const override;
};

};
