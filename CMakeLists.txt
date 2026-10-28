cmake_minimum_required(VERSION 3.16)

project(DataVisualisationLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# ---------- Histogram library ----------
add_library(dataviz_histogram
    src/histogram.cpp
)

target_include_directories(dataviz_histogram
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---------- Renderer library (used by the histogram example) ----------
add_library(dataviz_renderer
    src/renderer.cpp
)

target_include_directories(dataviz_renderer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ---------- Histogram example ----------
add_executable(histogram_example
    examples/histogram_example.cpp
)

target_link_libraries(histogram_example
    PRIVATE dataviz_histogram dataviz_renderer
)

# ---------- Histogram test ----------
add_executable(histogram_test
    tests/histogram_test.cpp
)

target_link_libraries(histogram_test
    PRIVATE dataviz_histogram
)

add_test(NAME HistogramTest COMMAND histogram_test)