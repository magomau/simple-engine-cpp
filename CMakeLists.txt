cmake_minimum_required(VERSION 3.21)

project(SimpleEngineCpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenGL REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

add_executable(SimpleEngine
    src/main.cpp
    src/engine/Engine.cpp
    src/engine/Window.cpp
    src/engine/Application.cpp
    src/engine/Input.cpp
    src/engine/Renderer.cpp
    src/engine/Shader.cpp
    src/engine/GLFunctions.cpp
    src/engine/Transform.cpp
    src/engine/RenderObject.cpp
    src/engine/Scene.cpp
    src/engine/Camera.cpp
    src/engine/Mesh.cpp
    src/engine/PrimitiveFactory.cpp
    src/core/Logger.cpp
)

target_include_directories(SimpleEngine PRIVATE src)

target_link_libraries(SimpleEngine PRIVATE
    OpenGL::GL
    SDL3::SDL3
    glm::glm
    imgui::imgui
    box2d::box2d
)
