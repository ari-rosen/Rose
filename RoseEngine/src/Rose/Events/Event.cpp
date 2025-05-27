#include "Rose/Events/Event.hpp"

namespace Rose {

bool Event::isInCatagory(EventCatagory catagory) {
    return getCatagoryFlags() & catagory;
}

EventDispatcher::EventDispatcher(Event &e)
    :m_Event(e) {}

} // namespace Rose
