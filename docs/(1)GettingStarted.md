
# Getting Started

After compiling the engine into a library and linking it, try this test:

```cpp
// main.cpp

#include <Rose/Rose.hpp>

int main() {
    Rose::Application app;
    app.run();
}
```
This should result in a blank window opening with the title ```Rose Engine```

You can edit the title of the window in the ```Rose::Application``` constructor
```cpp
Rose::Application app(1920, 1080, "Custom Title"); 
```

To create a starter scene, create a derived class of ```Rose::Scene```
```cpp
class CustomScene : public Rose::Scene {
public:
	void onStart() override {
	}
	void onUpdate(float DeltaTime) override {
	}
	void onEvent(Rose::Event &e) override {
	}
};
```
In order to use the scene, create an instance of it and set the application's active scene
```cpp
std::shared_ptr<CustomScene> scene = std::make_shared<CustomScene>();
app.setActiveScene(scene);
app.run();
```
There are three main methods in a ```Rose::Scene```:
* ```onStart()``` -> called once when the scene is attatched
* ```onUpdate(float DeltaTime)``` -> called once every frame
* ```onEvent(Rose::Event &e)``` -> called when a ```Rose::Event``` is triggered

To test the scene's functionality, write a simple print statement inside each of the methods

Also note that ```std::endl``` or ```std::flush``` is necessary to see output before the app is closed

onStart Example:
```cpp
void onStart() {
	std::cout << "Hello, World!" << std::endl;
}
```
Output:
```
Hello World!
```
--------
onUpdate example:
```cpp
void onUpdate(float DeltaTime) {
	std::cout << "Hello, World!" << std::endl;
}
```
Output:
```
Hello, World!
Hello, World!
Hello, World! 
...
```
---
onEvent example:
```cpp
void onEvent(Rose::Event &e) {
	std::cout << e.getName() << std::endl;
}
```
Example Output:
```
MouseMoved
MouseMoved
MouseButtonPressed
WindowCloseEvent
```

