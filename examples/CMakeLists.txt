cmake_minimum_required(VERSION 3.16)

project(DataVisualizationLibrary VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

target_include_directories(dataviz PUBLIC include)

# Full-library demo plus standalone examples for individual modules.
add_executable(dataviz_example examples/example.cpp)
target_link_libraries(dataviz_example PRIVATE dataviz)

add_executable(kdeplot_example examples/kdeplot_example.cpp)
target_link_libraries(kdeplot_example PRIVATE dataviz)

add_executable(axis_example examples/axis_example.cpp)
target_link_libraries(axis_example PRIVATE dataviz)

add_executable(statistics_example examples/statistics_example.cpp)
target_link_libraries(statistics_example PRIVATE dataviz)

enable_testing()

# Each test is independently runnable. Use Debug builds to keep asserts enabled.
function(add_dataviz_test target source)
    add_executable(${target} ${source})
    target_link_libraries(${target} PRIVATE dataviz)
    if(MSVC)
        target_compile_options(${target} PRIVATE /UNDEBUG)
    else()
        target_compile_options(${target} PRIVATE -UNDEBUG)
    endif()
    add_test(NAME ${target} COMMAND ${target})
endfunction()

add_dataviz_test(dataviz_tests tests/test_library.cpp)
add_dataviz_test(test_kdeplot tests/test_kdeplot.cpp)
add_dataviz_test(test_axis tests/test_axis.cpp)
add_dataviz_test(test_statistics tests/test_statistics.cpp)
add_dataviz_test(test_components tests/test_components.cpp)

# Individual examples and tests for each remaining module.
add_executable(dataloader_example examples/dataloader_example.cpp)
target_link_libraries(dataloader_example PRIVATE dataviz)
add_dataviz_test(test_dataloader tests/test_dataloader.cpp)

add_executable(dataprocessor_example examples/dataprocessor_example.cpp)
target_link_libraries(dataprocessor_example PRIVATE dataviz)
add_dataviz_test(test_dataprocessor tests/test_dataprocessor.cpp)

add_executable(countplot_example examples/countplot_example.cpp)
target_link_libraries(countplot_example PRIVATE dataviz)
add_dataviz_test(test_countplot tests/test_countplot.cpp)

add_executable(histogram_example examples/histogram_example.cpp)
target_link_libraries(histogram_example PRIVATE dataviz)
add_dataviz_test(test_histogram tests/test_histogram.cpp)

add_executable(annotation_example examples/annotation_example.cpp)
target_link_libraries(annotation_example PRIVATE dataviz)
add_dataviz_test(test_annotation tests/test_annotation.cpp)

add_executable(renderer_example examples/renderer_example.cpp)
target_link_libraries(renderer_example PRIVATE dataviz)
add_dataviz_test(test_renderer tests/test_renderer.cpp)

add_executable(imageexporter_example examples/imageexporter_example.cpp)
target_link_libraries(imageexporter_example PRIVATE dataviz)
add_dataviz_test(test_imageexporter tests/test_imageexporter.cpp)

