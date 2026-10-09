# Group 4 Skeleton: Library Architecture

## C++ LANGUAGE

## Library

dataviz: a reusable C++ library for loading data, computing summaries,
and producing count plots, histograms and KDE plots as image files.

## Namespace and folders

- Namespace: dataviz
- Public headers: include/dataviz/ (PascalCase names, e.g. Histogram.hpp)
- Implementations: src/ (e.g. Histogram.cpp)
- Tests: tests/
- Examples: examples/

## Pipeline

DataLoader -> DataProcessor -> Statistics
-> CountPlot / Histogram / KDEPlot
-> Axis -> Annotations -> Renderer -> ImageExporter

## Module purposes

- **DataLoader:** reads data from a file into memory.
- **DataProcessor:** cleans and prepares the loaded data for plotting.
- **Statistics:** computes summary values such as mean, median, standard deviation, min and max.
- **CountPlot:** counts how often each category occurs and prepares the bars for a count plot.
- **Histogram:** divides numeric data into bins and counts the values in each bin.
- **KDEPlot:** estimates a smooth density curve from numeric data.
- **Axis:** converts data values into plot coordinates and chooses the tick marks.
- **Annotations:** holds the titles, axis labels and notes that go on a plot.
- **Renderer:** builds the SVG content of a plot from its data, axes and annotations.
- **ImageExporter:** writes the finished SVG to a file.

## Design decisions

- Invalid input (empty data, zero bins) throws std::invalid_argument.
- Image format: (SVG (Scalable Vector Graphics). An SVG file is text, so the library builds
the image as text elements and writes them to a .svg file. No external
libraries are needed.).
- C++17, built with CMake.

## Open questions

- Which dataset will our examples use?
- Which image format do we export?
- How do the plot classes hand their data to Renderer?
