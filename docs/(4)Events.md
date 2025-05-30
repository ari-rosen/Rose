# Events
Events in Rose all fall under the ```Rose::Event``` base class.
All events have ```getName```, ```getEventType```, and ```getCatagoryFlags``` methods

When an event is triggered, that event is sent to the scene or application's ```onEvent``` function.

Currently supported events:

### Key Pressed
```Rose::KeyPressedEvent```

Triggered when a key is pressed

Additional methods:

* ```getKeyCode``` -> returns the ```Rose::KeyCode``` corresponding to the key pressed
* ```getRepeatCount``` -> returns the number of times the key has been triggered if held

### Key Released
```Rose::KeyReleasedEvent```

Triggered when a key is released

Additional methods:

* ```getKeyCode``` -> returns the number corresponding to the key pressed

### Mouse Moved
```Rose::MouseMovedEvent```

Triggered when the mouse's position changes

Additional methods:

* ```getX``` -> Returns the new mouse x position
* ```getY``` -> Returns the new mouse y position

### Mouse Button Pressed
```Rose::MouseButtonPressedEvent```

Triggered when any button on the mouse is pressed

Additional methods:

* ```getButtonPressed``` -> Returns which button was pressed
* ```getAction``` -> Returns what action the mouse did (click/release)
* ```getMods``` -> Returns what modifier keys were held (shift, ctrl, etc.)

### Window Closed
```Rose::WindowCloseEvent```

Triggered when the user exits the program

No additional methods


## Event Handling
Events can be handled in an onEvent function in ```Rose::Scene``` and ```Rose::Application```
```cpp
void onEvent(Rose::Event &e);
```
To filter for specific events, use ```Rose::EventDispatcher```
Example to dispatch ```Rose::KeyPressed``` in order to use ```getKeyCode```
```cpp
void onKeyPress(Rose::KeyPressedEvent &e) {
	std::cout << e.getKeyCode() << std::endl;
}
void onEvent(Rose::Event &e) override {
	Rose::EventDispatcher dispatcher(e);
	
	dispatcher.dispatch<Rose::KeyPressedEvent>(
		[this](Rose::KeyPressedEvent &keyEvent) {
			onKeyPress(keyEvent);
		}
	);
}
```
Alternatively, you can use the ```ROSE_BIND_EVENT_FUNC``` macro for the same effect
```cpp
dispatcher.dispatch<Rose::KeyPressedEvent>(ROSE_BIND_EVENT_FUNC(onKeyPress));
```

to add support for multiple different event types, it's as simple as adding more ```dispatch``` calls
```cpp
dispatcher.dispatch<Rose::KeyPressedEvent>(ROSE_BIND_EVENT_FUNC(onKeyPress));

dispatcher.dispatch<Rose::MouseMovedEvent>(ROSE_BIND_EVENT_FUNC(onMouseMove));

dispatcher.dispatch<Rose::MouseButtonPressedEvent>(ROSE_BIND_EVENT_FUNC(onClick));
```

