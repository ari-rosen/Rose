/*
Example code for creating a blank application
It is *nececary* to define what platform or the engine will not compile
for macOS, use ROSE_PLATFORM_MACOS
*/

#define ROSE_PLATFORM_MACOS
#include <Rose.hpp>

int main() {
    Rose::Application app("My Application Title", 600, 600);
    app.run();
}
