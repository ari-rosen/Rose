# Game Objects and the ECS
## Game Objects
To make objects (entities) in Rose, ```Rose::GameObject``` is used.
```cpp
Rose::GameObject exampleObject;
```
To register the object into the scene, the scene's ```createGameObject()``` method can be used.
```cpp
class ExampleScene : public Rose::Scene {
private:
	Rose::GameObject exampleObject;
public:
	void onStart() override {
		exampleObject = createGameObject();
	}
	void onUpdate(float DeltaTime) override {
	}
	void onEvent(Rose::Event &e) override {
	}
};
```
## Components
A ```Rose::GameObject``` is just an alias for an ```unsigned int```, so it does not contain any methods or components itself

Instead, a ```Rose::GameObject```'s components are stores within the scene to optimize performance

To add components to a ```Rose::GameObject``` that has been registered with ```createGameObject()```, you can call the ```addComponents``` method from ```Rose::Scene```

The ```addComponents``` method takes in the object as an argument, and the type of component as the template argument
```cpp
void onStart() override {
	exampleObject = createGameObject();
	addComponents<Rose::TransformComponent>(exampleObject);
}
```
In Rose, components are just structs that only contain data.
The ```Rose::TransformComponent``` struct contains a position, rotation (degrees), and scale (size in pixels)
```cpp
Rose::TransformComponent exampleTransform = {
	.Position = {0.0f, 0.0f},
	.Rotation = 0.0f,
	.Scale = 100.0f, 100.0f
};
```
To add the component to a game object that has that component registered with ```addComponent```, use the ```insertComponentData``` method from ```Rose::Scene```
```cpp
insertComponentData(exampleObject, exampleTransform);
```
In order to render an object to the screen, a ```Rose::ViewComponent``` is necessary.
```cpp
Rose::ViewComponent exampleView = {
	.Visible = true,
	.Layer = 0
};
insertComponentData(exampleObject, exampleView);
```
Full creation of a visible ```Rose::GameObject```
```cpp
class ExampleScene : public Rose::Scene {
private:
	Rose::GameObject exampleObject;
public:
	void onStart() override {
		exampleObject = createGameObject();
		addComponents<Rose::TransformComponent, Rose::ViewComponent>(exampleObject);
		
		Rose::TransformComponent exampleTransform = {
			.Position = {0.0f, 0.0f},
			.Rotation = 0.0f,
			.Scale = 100.0f, 100.0f
		};
		insertComponentData(exampleObject, exampleTransform);
		
		Rose::ViewComponent exampleView = {
			.Visible = true,
			.Layer = 0
		};
		insertComponentData(exampleObject, exampleView);
	}
	void onUpdate(float DeltaTime) override {
	}
	void onEvent(Rose::Event &e) override {
	}
};
```
Custom components can be created by just defining a new struct
```cpp
struct exampleComponent {
	float data;
};
```
To use a custom component, a scene's ```registerComponent``` method must be called before anything else involving it
```cpp
registerComponent<exampleComponent>();
```
To edit values of components, use the scene's ```GetComponent``` method to return a reference of the desired component
```cpp
void onUpdate(float DeltaTime) override {
	Rose::TransformComponent &transform = getComponent<Rose::TransformComponent>(exampleObject);
	transform.Position.x += 1 * DeltaTime;
}
```
