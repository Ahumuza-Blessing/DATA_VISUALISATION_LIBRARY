
cmake_minimum_required(VERSION 3.16)

project(DataVisualizationLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build the modules that currently have implementations.
add_library(dataviz
    src/DataLoader.cpp
    src/DataProcessor.cpp
    src/Statistics.cpp
    src/CountPlot.cpp
    src/Histogram.cpp
    src/KDEPlot.cpp
    src/Axis.cpp
    src/Annotation.cpp
    src/ImageExporter.cpp
)

target_include_directories(dataviz PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Export generated SVG files to the project's output folder.
target_compile_definitions(dataviz PRIVATE
    DATAVIZ_DEFAULT_OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/output"
)

# Existing example that does not require Renderer.cpp.
add_executable(kdeplot_example
    examples/kdeplot_example.cpp
)

target_link_libraries(kdeplot_example PRIVATE dataviz)

# Register the existing module tests.
enable_testing()

function(add_dataviz_test name)
    add_executable(${name} tests/${name}.cpp)
    target_link_libraries(${name} PRIVATE dataviz)

    if(MSVC)
        target_compile_options(${name} PRIVATE /UNDEBUG)
    else()
        target_compile_options(${name} PRIVATE -UNDEBUG)
    endif()

    add_test(NAME ${name} COMMAND ${name})
endfunction()

add_dataviz_test(test_dataloader)
add_dataviz_test(test_dataprocessor)
add_dataviz_test(test_statistics)
add_dataviz_test(test_countplot)
add_dataviz_test(test_histogram)
add_dataviz_test(test_kdeplot)
add_dataviz_test(test_axis)
add_dataviz_test(test_annotation)
add_dataviz_test(test_imageexporter)
