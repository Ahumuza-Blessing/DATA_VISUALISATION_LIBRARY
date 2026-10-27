
cmake_minimum_required(VERSION 3.16)

project(DataVisualisationLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(renderer.cpp
)

target_include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(renderer_demo
    examples/renderer_demo.cpp
)

target_link_libraries(renderer_demo)
enable_testing()

add_executable(renderer_test
    tests/renderer_test.cpp
)

target_link_libraries(renderer_test)

add_test(NAME RendererTest COMMAND renderer_test)
