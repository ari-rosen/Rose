#include "Rose/Events/MouseEvent.hpp"
#include "Rose/Events/Event.hpp"

namespace Rose {

MouseMovedEvent::MouseMovedEvent(double xPos, double yPos)
    : m_XPos(xPos), m_YPos(yPos) {}

EventType MouseMovedEvent::getStaticType() {
    return EventType::MouseMoved;
}

EventType MouseMovedEvent::getEventType() const {
    return getStaticType();
}

const char *MouseMovedEvent::getName() const {
    return "MouseMoved";
}

int8_t MouseMovedEvent::getCatagoryFlags() const {
    return MouseEventCatagory | InputEventCatagory;
}

MouseButtonPressedEvent::MouseButtonPressedEvent(int32_t button, int32_t action, int32_t mods)
    : m_Button(button), m_Action(action), m_Mods(mods) {}

EventType MouseButtonPressedEvent::getStaticType() {
    return EventType::MouseButtonPressed;
}

EventType MouseButtonPressedEvent::getEventType() const {
    return getStaticType();
}

const char *MouseButtonPressedEvent::getName() const {
    return "MouseButtonPressed";
}

int8_t MouseButtonPressedEvent::getCatagoryFlags() const {
    return MouseEventCatagory | InputEventCatagory;
}

} // namespace Rose
