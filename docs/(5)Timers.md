# Timers

Timers can be created in a ```Rose::Scene``` to manage things like animations and miscellaneous timing needs

To create a ```Rose::TimerID```, use the ```createTimer``` method

the method is defined as followed:
```cpp
  Rose::TimerID createTimer(uint32_t milliseconds, const std::function<void()> &func, bool repeat);
```
The first parameter is the number of milliseconds to wait in order to execute the next parameter, the callback function. The final parameter is a flag to set a reacurring timer

To create and start a timer, the ```startTimer``` method is used
```cpp
Rose::TimerID timer = createTimer(5000, callback, false);
startTimer(timer);  
```

To pause a timer on command, use the ```pauseTimer``` method
```cpp
pauseTimer(timer);
```

To resume a timer, use the ```startTimer``` method from before
```cpp
startTimer(timer);
```

To stop a timer permenetly, use the ```deleteTimer``` method

This is useful to terminate a reapeating timer
```cpp
deleteTimer(timer);
```
