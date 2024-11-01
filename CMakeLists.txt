﻿## --- Project configuration --- ##
cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

## --- Compiler configuration --- ##
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
include_directories("include/")

## --- Packages configuration --- ##
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)

## --- Executable configuration --- ##
add_executable(LearnOpenGL "source/main.cpp"
    # Common modules
    "source/common/image.cpp"
    "source/common/utility.cpp"

    # External modules
    "source/external/stb_image.c"

    # Graphics modules
    "source/graphics/camera.cpp"
    "source/graphics/cube.cpp"
    "source/graphics/light.cpp"
    "source/graphics/shader_program.cpp"
    "source/graphics/texture.cpp"
    "source/graphics/window.cpp"
)
target_link_libraries(LearnOpenGL PRIVATE
    fmt::fmt
    spdlog::spdlog
    glfw
    GLEW::GLEW
    ${OPENGL_LIBRARY}
    glm::glm
)
