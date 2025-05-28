cmake_minimum_required(VERSION 3.10)

project(RoseEngine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

add_library(glad STATIC
    RoseEngine/dependencies/glad/src/glad.c
)

target_include_directories(glad PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/RoseEngine/dependencies/glad/include
)

add_library(RoseEngine SHARED
    RoseEngine/src/Rose/Core/Application.cpp
    RoseEngine/src/Rose/Core/Window.cpp
    RoseEngine/src/Rose/Core/Scene.cpp
    RoseEngine/src/Rose/Core/Timer.cpp
    RoseEngine/src/Rose/Util/File.cpp
    RoseEngine/src/Rose/Events/Event.cpp
    RoseEngine/src/Rose/Events/KeyEvent.cpp
    RoseEngine/src/Rose/Events/ApplicationEvent.cpp
    RoseEngine/src/Rose/Events/MouseEvent.cpp
    RoseEngine/src/Rose/ComponentSystem/ComponentArray.cpp
    RoseEngine/src/Rose/ComponentSystem/ObjectManager.cpp
    RoseEngine/src/Rose/ComponentSystem/SystemManager.cpp
    RoseEngine/src/Rose/Graphics/Buffer.cpp
    RoseEngine/src/Rose/Graphics/Shader.cpp
    RoseEngine/src/Rose/Graphics/Renderer.cpp
    RoseEngine/src/Rose/Graphics/Image.cpp
    RoseEngine/src/Rose/Graphics/Texture.cpp
    RoseEngine/src/Rose/Graphics/TextureParam.cpp
)

target_precompile_headers(RoseEngine PRIVATE RoseEngine/src/pch.hpp)

target_compile_definitions(RoseEngine PRIVATE
    ROSE_PLATFORM_MACOS
    ROSE_BUILD_DYLIB
)

target_include_directories(RoseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/RoseEngine/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/RoseEngine/dependencies/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/RoseEngine/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/RoseEngine/dependencies/
)

add_subdirectory(RoseEngine/dependencies/glfw)

target_link_libraries(RoseEngine PRIVATE
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    glfw
    glad
)
