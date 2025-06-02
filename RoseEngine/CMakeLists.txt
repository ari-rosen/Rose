cmake_minimum_required(VERSION 3.10)

project(RoseEngine C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(RoseEngine SHARED
    src/Rose/Core/Application.cpp
    src/Rose/Core/Window.cpp
    src/Rose/Core/Scene.cpp
    src/Rose/Core/Timer.cpp
    src/Rose/Core/Input.cpp
    src/Rose/Util/File.cpp
    src/Rose/Events/Event.cpp
    src/Rose/Events/KeyEvent.cpp
    src/Rose/Events/ApplicationEvent.cpp
    src/Rose/Events/MouseEvent.cpp
    src/Rose/ComponentSystem/ComponentArray.cpp
    src/Rose/ComponentSystem/ObjectManager.cpp
    src/Rose/ComponentSystem/SystemManager.cpp
    src/Rose/Graphics/Buffer.cpp
    src/Rose/Graphics/Shader.cpp
    src/Rose/Graphics/Renderer.cpp
    src/Rose/Graphics/UIRenderer.cpp
    src/Rose/Graphics/Image.cpp
    src/Rose/Graphics/Texture.cpp
    src/Rose/Graphics/TextureParam.cpp
)

target_precompile_headers(RoseEngine PRIVATE src/pch.hpp)

target_compile_definitions(RoseEngine PRIVATE
    ROSE_PLATFORM_MACOS
    ROSE_BUILD_DYLIB
    ROSE_ENGINE_SRC_PATH="${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_include_directories(RoseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freetype/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/freetype/include/freetype2
)

add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glfw)

set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "" FORCE)
add_subdirectory(dependencies/freetype)

find_library(COCOA_FRAMEWORK Cocoa REQUIRED)
find_library(OpenGL_FRAMEWORK OpenGL REQUIRED)
find_library(IOKIT_FRAMEWORK IOKit REQUIRED)

target_link_libraries(RoseEngine PRIVATE
    ${COCOA_FRAMEWORK}
    ${OpenGL_FRAMEWORK}
    ${IOKIT_FRAMEWORK}
    glfw
    glad
    freetype
)

install(TARGETS RoseEngine
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
