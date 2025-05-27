#pragma once

#include "Rose/Core/Core.hpp"

namespace Rose {

struct ROSE_API Timer {
    const std::function<void()> callback;
    uint32_t ms;
    uint32_t remainingTime;
    bool repeat;
    bool active;
    
    Timer(const std::function<void()> &func) : callback(func) {};
};

using TimerID = uint32_t;

class ROSE_API TimerManager {
public:
    TimerManager();

    TimerID createTimer(uint32_t miliseconds, const std::function<void()> &func, bool repeat);

    void startTimer(TimerID id);
    void pauseTimer(TimerID id);
    void deleteTimer(TimerID id);

    void onUpdate(float DeltaTime);
private:
    TimerID m_AvailiableTimerID;
    std::unordered_map<TimerID, std::shared_ptr<Timer>> m_TimerMap{};
};

}
