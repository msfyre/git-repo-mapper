cmake_minimum_required(VERSION 3.11)
project(GitMapper LANGUAGES CXX)

# CPP standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OPENGL_GL_PREFERENCE GLVND)

add_executable(GitMapper src/main.cpp)

find_package(Curses REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL3 REQUIRED)

add_subdirectory(external/libgit2)

add_library(engine
	src/engine/engine.cpp
	src/engine/renderer.cpp
	src/engine/runtime.cpp
)

add_library(diagnostics
	src/diagnostics/cpu.cpp
)

target_include_directories(engine PUBLIC includes)
target_include_directories(diagnostics PUBLIC includes)

target_include_directories(GitMapper PRIVATE includes ${CURSES_INCLUDE_DIR})

target_link_libraries(engine PUBLIC diagnostics ncurses OpenGL::GL glm::glm SDL3::SDL3)
target_link_libraries(GitMapper PRIVATE engine ${CURSES_LIBRARIES})

