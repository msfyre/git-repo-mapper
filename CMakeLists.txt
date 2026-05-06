cmake_minimum_required(VERSION 3.14)
project(GitMapper VERSION 0.0 LANGUAGES CXX)

# CPP standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(program src/main.cpp)

# SDL3
find_package(SDL3 REQUIRED)
target_link_libraries(program PRIVATE SDL3::SDL3)

# includes
target_include_directories(program PRIVATE includes)

add_library(engine
	src/engine/engine.cpp
	src/engine/renderer.cpp
	src/engine/runtime.cpp
)

target_include_directories(engine PUBLIC includes)

target_link_libraries(program PRIVATE engine)
