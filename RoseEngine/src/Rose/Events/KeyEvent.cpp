#include "Rose/Events/KeyEvent.hpp"

namespace Rose {

// Key Event
KeyEvent::KeyEvent(int32_t keyCode)
    : m_KeyCode(keyCode) {}

KeyCode KeyEvent::getKeyCode() const {
    return static_cast<KeyCode>(m_KeyCode);
}

int8_t KeyEvent::getCatagoryFlags() const {
    return KeyboardEventCatagory | InputEventCatagory;
}

// Key Pressed

KeyPressedEvent::KeyPressedEvent(int32_t keyCode, int32_t repeatCount)
    : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

EventType KeyPressedEvent::getStaticType() {
    return EventType::KeyPressed;
}

EventType KeyPressedEvent::getEventType() const {
    return getStaticType();
}

const char *KeyPressedEvent::getName() const {
    return "KeyPressedEvent";
}

int32_t KeyPressedEvent::getRepeatCount() const {
   return m_RepeatCount; 
}

// Key Released

KeyReleasedEvent::KeyReleasedEvent(int32_t keyCode)
    : KeyEvent(keyCode) {}

EventType KeyReleasedEvent::getStaticType() {
    return EventType::KeyReleased;
}
EventType KeyReleasedEvent::getEventType() const {
    return getStaticType();
}

const char *KeyReleasedEvent::getName() const {
    return "KeyReleasedEvent";
}

} // namespace Rose
