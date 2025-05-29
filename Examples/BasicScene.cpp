/*
Example code for creating a scene, and a basic game object
*/

#define ROSE_PLATFORM_MACOS
#include <Rose.hpp>

#include <memory> // for std::make_shared

class ExampleScene : public Rose::Scene {
private:
  Rose::GameObject object;
public:
  void onStart() override {
    // Step 1: Register the object
    object = createGameObject();
    
    // Step 2: Add the components to the object
    addComponents<Rose::TransformComponent, Rose::ViewComponent>(object);

    // Step 3: Add the data to the components
    insertComponentData(object, Rose::TransformComponent{
      .Position = {0.0f, 0.0f},
      .Rotation = 0.0f,
      .Scale = {150.0f, 150.0f}
    });
    insertComponentData(object, Rose::ViewComponent{
      .Visable = true,
      .Layer = 0
    }); 
  }

  void onUpdate(float DeltaTime) override {
  }
};

int main() {
  Rose::Application app("Title", 800, 600);
  app.setActiveScene(std::make_shared<ExampleScene>());
  app.run();
}
