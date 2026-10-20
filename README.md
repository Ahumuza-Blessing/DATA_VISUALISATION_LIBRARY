# CPP Data Visualization Library — Group 4

## 1. Project Description

dataviz is a reusable C++ library for loading data, processing it, calculating basic statistical summaries, and producing simple visualizations.

The library is designed to support:

- Count plots
- Histograms
- KDE plots
- Axis scaling
- Labels and annotations
- Plot rendering
- Image export

The project is intended to demonstrate C++ and Object-Oriented Programming concepts while building a reusable data visualization library.

---

## 2. Group Members

ADONGA PHILLIP  
AHUMUZA BLESSING  
ATWINE JEANES  
TWINOMUJUNI ROMEO  
NAMUBIRU LOUISE  
MUGERWA SHADRACK STEPHEN  
SERUGYA FAHAD  
WALUGEMBE MUHAISINAH. N  
EGERU MICHAEL  
KISAKYE JEMIMA

---

## 3. Project Objectives

- Apply C++ and Object-Oriented Programming concepts.
- Build a reusable C++ library.
- Load and process data.
- Generate basic statistical summaries.
- Create different types of plots.
- Export generated plots as image files.
- Organize the project using a clear library architecture.

---

## 4. Main Features

- Data loading
- Data preprocessing
- Statistical summaries
- Count plots
- Histograms
- KDE plots
- Axis scaling
- Labels and annotations
- Plot rendering
- SVG image export

---

## 5. Library Architecture

### Namespace

The library uses the namespace:

dataviz

### Processing Pipeline

DataLoader  
↓  
DataProcessor  
↓  
Statistics  
↓  
CountPlot / Histogram / KDEPlot  
↓  
Axis  
↓  
Annotations  
↓  
Renderer  
↓  
ImageExporter

---

## 6. Main Modules

### DataLoader

Reads data from a file and loads it into memory.

### DataProcessor

Cleans, validates, and prepares the loaded data for analysis and plotting.

### Statistics

Calculates statistical summaries such as:

- Mean
- Median
- Standard deviation
- Minimum
- Maximum

### CountPlot

Counts how often each category occurs and prepares the data required to draw a count plot.

### Histogram

Divides numerical data into bins and counts how many values fall into each bin.

### KDEPlot

Estimates a smooth density curve from numerical data.

### Axis

Handles axis scaling, converts data values into plot coordinates, and determines tick positions.

### Annotations

Stores plot information such as:

- Plot titles
- X-axis labels
- Y-axis labels
- Notes and annotations

### Renderer

Builds the SVG representation of the plot using plot data, axes, and annotations.

### ImageExporter

Writes the generated SVG content to an output file.

---

## 7. Project Structure

CPP-Data-Visualization-Library/  
├── data/  
│   ├── input/          # Input datasets  
│   └── output/         # Exported plot files  
│  
├── examples/           # Example programs using the library  
│  
├── include/  
│   └── dataviz/        # Public header files  
│       ├── DataLoader.hpp  
│       ├── DataProcessor.hpp  
│       ├── Statistics.hpp  
│       ├── CountPlot.hpp  
│       ├── Histogram.hpp  
│       ├── KDEPlot.hpp  
│       ├── Axis.hpp  
│       ├── Annotations.hpp  
│       ├── Renderer.hpp  
│       └── ImageExporter.hpp  
│  
├── reports/            # Weekly project reports  
│  
├── src/                # C++ implementation files  
│   ├── DataLoader.cpp  
│   ├── DataProcessor.cpp  
│   ├── Statistics.cpp  
│   ├── CountPlot.cpp  
│   ├── Histogram.cpp  
│   ├── KDEPlot.cpp  
│   ├── Axis.cpp  
│   ├── Annotations.cpp  
│   ├── Renderer.cpp  
│   └── ImageExporter.cpp  
│  
├── tests/              # Unit and integration tests  
│  
├── CMakeLists.txt  
└── README.md

---

## 8. Naming Conventions

Public header files use PascalCase names.

Examples:

Histogram.hpp  
DataLoader.hpp  
Axis.hpp  
Renderer.hpp

Implementation files use matching names:

Histogram.cpp  
DataLoader.cpp  
Axis.cpp  
Renderer.cpp

---

## 9. Design Decisions

### C++ Standard

The project uses:

C++17

### Build System

The project uses:

CMake

### Error Handling

Invalid inputs such as:

- Empty datasets
- Invalid values
- Zero histogram bins

should throw:

std::invalid_argument

### Image Format

The library exports plots as:

SVG — Scalable Vector Graphics

SVG was selected because it is text-based and can be generated directly by the C++ library without requiring an external graphics library.

The renderer builds SVG elements as text and the ImageExporter writes the final content to a .svg file.

---

## 10. Requirements

- C++17-compatible compiler
- CMake
- Standard C++ Library

No external graphics library is required for the initial SVG implementation.

---

## 11. Remaining Design Questions

- Which dataset will be used in the example programs?
- What common plot-data structure should be passed from the plot classes to Renderer?
- What exact interface should each plot class expose?