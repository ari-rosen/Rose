#pragma once

#include "Rose/Core/Core.hpp"
#include "Rose/Events/Event.hpp"

namespace Rose {

class ROSE_API MouseMovedEvent : public Event {
public:
    MouseMovedEvent(double xPos, double yPos);

    inline double getX() const { return m_XPos; }
    inline double getY() const { return m_YPos; }
    
    static EventType getStaticType();
    EventType getEventType() const override;
    const char *getName() const override;
    int8_t getCatagoryFlags() const override;

private:
    double m_XPos, m_YPos;
};

class ROSE_API MouseButtonPressedEvent : public Event {
public:
    MouseButtonPressedEvent(int32_t button, int32_t action, int32_t mods);

    inline int32_t getButtonPressed() const { return m_Button; }
    inline int32_t getAction() const { return m_Action; }
    inline int32_t getMods() const { return m_Mods; }

    static EventType getStaticType();
    EventType getEventType() const override;
    const char * getName() const override;
    int8_t getCatagoryFlags() const override;

private:
    int32_t m_Button, m_Action, m_Mods;
};

} // namespace Rose
