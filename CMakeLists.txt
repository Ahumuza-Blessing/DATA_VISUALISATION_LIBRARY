
cmake_minimum_required(VERSION 3.16)

project(DataVisualizationLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build all modules.
add_library(dataviz
    src/DataLoader.cpp
    src/DataProcessor.cpp
    src/Statistics.cpp
    src/CountPlot.cpp
    src/Histogram.cpp
    src/KDEPlot.cpp
    src/Axis.cpp
    src/Annotation.cpp
    src/Renderer.cpp
    src/ImageExporter.cpp
)

target_include_directories(dataviz PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Export generated SVG files to the project's output folder.
target_compile_definitions(dataviz PRIVATE
    DATAVIZ_DEFAULT_OUTPUT_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data/output"
)

# Build all runnable examples against the integrated library.
foreach(example IN ITEMS countplot histogram kdeplot complete_library)
    add_executable(${example}_example examples/${example}_example.cpp)
    target_link_libraries(${example}_example PRIVATE dataviz)
endforeach()

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

add_dataviz_test(renderer_test)
