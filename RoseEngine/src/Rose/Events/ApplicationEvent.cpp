#include "Rose/Events/ApplicationEvent.hpp"

namespace Rose {

// Window Resize Event

WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height) {}

EventType WindowResizeEvent::getStaticType() {
    return EventType::WindowResize;    
}

EventType WindowResizeEvent::getEventType() const {
    return getStaticType();
}

const char *WindowResizeEvent::getName() const {
    return "WindowResize";
}

int8_t WindowResizeEvent::getCatagoryFlags() const {
    return ApplicationEventCatagory;
}

// Window Close Event

EventType WindowCloseEvent::getStaticType() {
    return EventType::WindowClose;
}

EventType WindowCloseEvent::getEventType() const {
    return getStaticType();
}

const char *WindowCloseEvent::getName() const {
    return "WindowCloseEvent";
}

int8_t WindowCloseEvent::getCatagoryFlags() const {
    return ApplicationEventCatagory;
}

};
