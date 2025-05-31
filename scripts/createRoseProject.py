import os

ROOT_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

def create_dir(path):
    os.makedirs(path, exist_ok=True)
    print(f"[+] Created directory: {path}")

def create_file(path, content=""):
    with open(path, 'w') as f:
        f.write(content)
    print(f"[+] Created file: {path}")

def create_rose_app(project_name):
    project_dir = os.path.join(ROOT_DIR, "Projects", project_name)
    src_dir = os.path.join(project_dir, "src")
    assets_dir = os.path.join(project_dir, "Assets")
    scenes_dir = os.path.join(assets_dir, "Scenes")
    textures_dir = os.path.join(assets_dir, "Textures")

    # Create folders
    create_dir(project_dir)
    create_dir(src_dir)
    create_dir(assets_dir)
    create_dir(scenes_dir)
    create_dir(textures_dir)

    # Create CMakeLists.txt
    create_file(os.path.join(project_dir, "CMakeLists.txt"), f"""\
cmake_minimum_required(VERSION 3.10)
project({project_name})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable({project_name}
    src/main.cpp
)

add_subdirectory(
    ../../RoseEngine
    RoseEngine-build
)

target_compile_definitions(RoseEngine PRIVATE ROSE_ASSETS_PATH=\"${{CMAKE_SOURCE_DIR}}/Assets\")

target_include_directories({project_name} PRIVATE ${{CMAKE_SOURCE_DIR}}/../../RoseEngine/src)

target_link_libraries({project_name} RoseEngine)
""")

    # Create main.cpp
    create_file(os.path.join(src_dir, "main.cpp"), """\
#define ROSE_PLATFORM_MACOS
#include <Rose.hpp>

class MainScene : public Rose::Scene {
public:
    void onStart() override {
    }

    void onUpdate(float DeltaTime) override {
    }

    void onEvent(Rose::Event &e) override {
    }
};

int main() {
    Rose::Application app;
    app.setActiveScene(std::make_shared<MainScene>());
    app.run();
    return 0;
}
""")

    # Create README.md
    create_file(os.path.join(project_dir, "README.md"), f"# {project_name} Rose App")

if __name__ == "__main__":
    project = input("Enter new project name: ").strip()
    if project:
        create_rose_app(project)
    else:
        print("[-] Invalid project name.")
