# Input

To use keyboard input in Rose, the ```Rose::Input``` singleton class is used

As of now, there is only one type of "dynamic" input in Rose, the keyboard.

To get keyboard input, check the desired key with ```Rose::Input::IsKeyDown```
```cpp
void onUpdate(float DeltaTime) override {
  if (Rose::Input::IsKeyDown(Rose::KEY_SPACE)) {
    std::cout << "Space Key Pressed" << std::endl
  }
}
```
> The KeyCode enum can be found in KeyCodes.hpp ; All GLFW keys are supported

this is different from using a ```Rose::KeyPressedEvent``` because when the event is triggered, there is a short delay and then it is repeated. It is ideal for somthing that needs the cooldown

Using ```Rose::Input::IsKeyDown``` is better for somthing like moving the player because there is no delay
