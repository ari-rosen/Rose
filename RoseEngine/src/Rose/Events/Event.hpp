#pragma once
#include "Rose/Core/Core.hpp"

namespace Rose {

enum class ROSE_API EventType {
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, // Application Events
    KeyPressed, KeyReleased, // Keyboard Events
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled // Mouse Events
};

enum ROSE_API EventCatagory {
    None = 0,
    ApplicationEventCatagory = BIT(0),
    InputEventCatagory = BIT(1),
    KeyboardEventCatagory = BIT(2),
    MouseEventCatagory = BIT(3),
    MouseButtonEventCatagory = BIT(4)
};

class ROSE_API Event {
    friend class EventDispatcher;
public:
    virtual EventType getEventType() const = 0;
    virtual const char *getName() const = 0;
    virtual int8_t getCatagoryFlags() const = 0;     
  
    inline bool isHandled() { return m_Handled; }

    bool isInCatagory(EventCatagory catagory);
protected:
    bool m_Handled = false;
};

class ROSE_API EventDispatcher {
public:
    EventDispatcher(Event &e);

    template<typename event_t, typename func_t>
    void dispatch(const func_t &func) {
        if (m_Event.getEventType() == event_t::getStaticType()) {
            func(dynamic_cast<event_t&>(m_Event));
            m_Event.m_Handled = true;
        }
    }


private:
    Event &m_Event;
};

} // namespace Rose
