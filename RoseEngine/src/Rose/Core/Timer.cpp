#include "Rose/Core/Timer.hpp"

namespace Rose {

TimerManager::TimerManager() : m_AvailiableTimerID(0) {}

TimerID TimerManager::createTimer(uint32_t miliseconds, const std::function<void()> &func, bool repeat) {
    auto newTimer = std::make_shared<Timer>(func);
    newTimer->ms = miliseconds;
    newTimer->remainingTime = newTimer->ms;
    newTimer->repeat = repeat;
    newTimer->active = false;
    TimerID newID = m_AvailiableTimerID++;
    m_TimerMap[newID] = newTimer;
    return newID;
}

void TimerManager::startTimer(TimerID id) {
    auto it = m_TimerMap.find(id);
    if (it != m_TimerMap.end()) {
        it->second->active = true;
    }
}

void TimerManager::pauseTimer(TimerID id) {
    m_TimerMap[id]->active = false;
}

void TimerManager::deleteTimer(TimerID id) {
    auto it = m_TimerMap.find(id);
    if (it != m_TimerMap.end()) {
        m_TimerMap.erase(it);
    }
}

void TimerManager::onUpdate(float DeltaTime) {
    for (auto it = m_TimerMap.begin(); it != m_TimerMap.end(); ) {
        auto &[ID, timer] = *it;

        if (!timer->active) {
            ++it;
            continue;
        }

        timer->remainingTime -= DeltaTime * 1000;

        if (timer->remainingTime <= 0) {
            if (timer->repeat) {
                timer->remainingTime = timer->ms;
                timer->callback();
                ++it;
            }
            else {
                timer->active = false;
                timer->callback();
                it = m_TimerMap.erase(it);
            }
        }
        else {
            ++it;
        }
    }
}

}
