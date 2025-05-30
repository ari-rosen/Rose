#pragma once
#include "Rose/Core/Core.hpp"
#include "Rose/Events/Event.hpp"

#include "Rose/Core/KeyCode.hpp"

namespace Rose {

class ROSE_API KeyEvent : public Event {
public:
    KeyCode getKeyCode() const;

    int8_t getCatagoryFlags() const override; 
protected:
    KeyEvent(int32_t keyCode);
    int32_t m_KeyCode;
};

class ROSE_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int32_t keyCode, int32_t repeatCount);

    static EventType getStaticType(); 
    EventType getEventType() const override;
    const char *getName() const override;

    int32_t getRepeatCount() const;
private:
    int32_t m_RepeatCount;
};

class ROSE_API KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int32_t keyCode);

    static EventType getStaticType();
    EventType getEventType() const override;
    const char *getName() const override;
};

} // namespace Rose
