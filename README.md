# C++ Data Visualization Library — Group 4

A reusable **C++17 data visualization library** that loads and prepares data,
calculates statistics, and creates **Count Plots, Histograms, and KDE Plots**.
The graphs are rendered as SVG images, without an external graphics library.

This project was organized by Group 4 as a practical application of C++
programming, modular design, and Object-Oriented Programming (OOP).

## 1. Group members and responsibilities

The names and allocations below follow the group's project records.

| Group member | Assigned module | Responsibility |
| --- | --- | --- |
| **ADONGA PHILLIP** | Data Loader | Read input datasets, initially CSV files |
| **ATWINE JEANES** | Data Processing | Clean and prepare loaded data |
| **AHUMUZA BLESSING** | Statistics | Implement descriptive statistical calculations |
| **EGERU MICHAEL** | Count Plot | Calculate frequencies of categorical values |
| **SERUGYA FAHAD** | Histogram | Group numerical values into bins |
| **MUGERWA SHADRACK STEPHEN** | KDE Plot | Estimate smooth numerical density curves |
| **TWINOMUJUNI ROMEO** | Axis | Calculate graph scales and tick values |
| **WALUGEMBE MUHAISINAH N.** | Annotations | Manage notes and labels added to graphs |
| **KISAKYE JEMIMA** | Renderer | Draw graph elements and produce SVG markup |
| **NAMUBIRU LOUISE** | Image Exporter | Save rendered SVG content as image files |

Each member works on a separate module. During integration, the modules share
their outputs rather than repeating calculations or drawing code.

## 2. Project objectives

- Apply C++ and relevant OOP concepts to a group software project.
- Develop a library with reusable and separately testable components.
- Read CSV datasets and prepare numerical or categorical values.
- Calculate basic statistical summaries.
- Produce complete Count Plots, Histograms, and KDE Plots.
- Include titles, axis labels, scales, tick marks, and optional annotations.
- Export the completed graphs as SVG files.
- Verify both individual modules and the combined library.

## 3. How the library works

```text
                  Input CSV file
                         |
                     DataLoader
                         |
                    DataProcessor
                         |
             +-----------+-----------+
             |                       |
      Categorical data         Numerical data
             |                       |
          CountPlot           Statistics
             |                       |
             |                +------+------+
             |                |             |
             |             Histogram      KDEPlot
             |                |             |
             +----------------+-------------+
                              |
                           Renderer
                     (uses Axis and
                    optional Annotation)
                              |
                         SVG content
                              |
                        ImageExporter
                              |
                       data/output/*.svg
```

For example, a histogram calculates its bins first, then gives those bins to
the **Renderer**, which uses **Axis** for scaling and places any requested
**Annotation** items on the graph. The **ImageExporter** saves the finished SVG.

The Renderer is shared by the three plot types. Each graph example calls the
other modules it needs, rather than implementing its own axis, drawing system,
or export code.

## 4. Main modules

| Module | What it does |
| --- | --- |
| `DataLoader` | Reads a CSV file into rows and columns of text |
| `DataProcessor` | Trims text, removes blank rows, extracts columns, and converts numerical text |
| `Statistics` | Calculates count, mean, median, minimum, maximum, variance, and standard deviation |
| `CountPlot` | Counts occurrences of categorical values |
| `Histogram` | Divides numeric data into bins and counts their values |
| `KDEPlot` | Uses a Gaussian kernel to estimate density points |
| `Axis` | Maps numerical values to drawing coordinates and generates ticks |
| `Annotation` | Stores positioned notes to appear on a plot |
| `Renderer` | Renders SVG graphs with title, axes, scales, labels, and optional annotations |
| `ImageExporter` | Creates the output directory if needed and saves SVG files |

**Important distinction:** In this version, `Annotation` stores additional
notes, while the plot title and axis labels are added by `Renderer`.
The module's class name is **`Annotation`** (singular), even though its
assigned project area is called *Annotations*.

## 5. Project structure

The main project files are organized as follows.

```text
├── data/
│   ├── input/
│   │   ├── Marks.csv
│   │   ├── monthly_sales.csv
│   │   ├── student_marks.csv
│   │   ├── subject_marks.csv
│   │   └── subject_preferences.csv
│   └── output/
├── include/
│   ├── DataLoader.hpp
│   ├── DataProcessor.hpp
│   ├── Statistics.hpp
│   ├── CountPlot.hpp
│   ├── Histogram.hpp
│   ├── KDEPlot.hpp
│   ├── Axis.hpp
│   ├── Annotation.hpp
│   ├── Renderer.hpp
│   └── ImageExporter.hpp
├── src/
│   ├── DataLoader.cpp
│   ├── DataProcessor.cpp
│   ├── Statistics.cpp
│   ├── CountPlot.cpp
│   ├── Histogram.cpp
│   ├── KDEPlot.cpp
│   ├── Axis.cpp
│   ├── Annotation.cpp
│   ├── Renderer.cpp
│   └── ImageExporter.cpp
├── examples/
│   ├── countplot_example.cpp
│   ├── histogram_example.cpp
│   ├── kdeplot_example.cpp
│   └── complete_library_example.cpp
├── tests/
│   ├── test_dataloader.cpp
│   ├── test_dataprocessor.cpp
│   ├── test_statistics.cpp
│   ├── test_countplot.cpp
│   ├── test_histogram.cpp
│   ├── test_kdeplot.cpp
│   ├── test_axis.cpp
│   ├── test_annotation.cpp
│   ├── test_renderer.cpp
│   └── test_imageexporter.cpp
├── reports/
├── .gitignore
├── CMakeLists.txt
└── README.md
```

The repository also keeps weekly project reports in `reports/`.

## 6. Examples: finished graphs

The `examples/` folder contains **four runnable demonstration programs**:

| Example | Output |
| --- | --- |
| `countplot_example.cpp` | Complete categorical count plot |
| `histogram_example.cpp` | Complete histogram of numerical marks |
| `kdeplot_example.cpp` | Complete KDE density curve |
| `complete_library_example.cpp` | Uses the main modules together and creates all three plots |

Each graph example includes a title, labeled axes, scales/ticks, and the
required plot elements. The countplot, histogram, and complete-library
examples read `data/input/student_marks.csv`; the standalone KDE example uses
an in-code sample. They save SVG files under `data/output/`.

An **example** demonstrates how someone can use the library. It does not
replace a correctness test.

## 7. Tests

CMake registers **ten tests**: tests for data loading and processing,
statistics, plot calculations, axes, annotations, image export, and SVG
rendering. They check expected results and selected invalid inputs.

A **test** verifies an expected result and reports success or failure.
A complete graph example may look correct but is not a substitute for tests.

## 8. Requirements and build instructions

- A C++17-compatible compiler, such as GCC, Clang, or MSVC.
- CMake **3.16 or newer**.
- The C++ standard library.

No third-party plotting or graphics framework is required.

From the repository root:

On Windows with MinGW, select its generator explicitly:

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
```

On systems where CMake can select the installed compiler automatically:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Then build and run the test suite:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

The test command runs all ten registered tests.

### Run the example programs

Run the examples from the repository root so their relative CSV paths resolve.
On Linux, or when using a single-configuration generator:

```bash
./build/countplot_example
./build/histogram_example
./build/kdeplot_example
./build/complete_library_example
```

On Windows, the executable location depends on the CMake generator. For a
Visual Studio build, executables are typically under `build/Debug/`, for
example `build/Debug/histogram_example.exe`. With a single-configuration
MinGW build, run them from PowerShell at the repository root:

```powershell
.\build\countplot_example.exe
.\build\histogram_example.exe
.\build\kdeplot_example.exe
.\build\complete_library_example.exe
```

## 9. Image output

By default, **all generated SVG images are saved to the project's
`data/output/` folder**, not to the build directory. The output folder is
created automatically if it does not exist.

```text
data/output/
├── countplot_example.svg
├── histogram_example.svg
├── kdeplot_example.svg
├── complete_countplot.svg
├── complete_histogram.svg
└── complete_kdeplot.svg
```

For example:

```cpp
ImageExporter::saveSVG(svg, "mygraph.svg");
```

This creates `data/output/mygraph.svg`. If an explicit output path is
provided, ImageExporter uses that requested path instead.

Generated `.svg` files are output artifacts; running examples does not
automatically commit them to GitHub.

## 10. C++ and OOP design

Our library uses **C++17**. We keep public declarations in `include/` and
implementations in `src/`; our examples and tests exercise those interfaces.

- **Encapsulation:** `Axis` keeps its ranges private and provides methods for
  scaling values, generating ticks, and updating ranges. `Annotation` hides
  its collection and lets us add, clear, and read notes.
- **Reusability:** We expose plot calculations and statistics through
  reusable static methods, then pass their results to the renderer to create
  SVG.
- **Separation of responsibilities:** We use `DataLoader` to read CSV data,
  `DataProcessor` to prepare it, plot modules to calculate plot data, `Axis`
  for coordinate scaling, `Renderer` to create SVG markup, and
  `ImageExporter` to write SVG files.

Our current design does not use a class-inheritance hierarchy or virtual
functions. We use `dataviz` as the CMake library target name; our C++ classes
are currently declared in the global namespace.

## 11. Naming conventions and integration

We keep public headers in `include/` and implementations in `src/`, using
matching names such as `Axis.hpp` and `Axis.cpp`. We match filename
capitalization in `#include` directives so our code also works on
case-sensitive filesystems, and keep calculations, rendering, and file export
in their respective modules.

As we add modules or examples, we update `CMakeLists.txt` along with the
relevant tests and documentation. Before sharing our changes, we build the
project, run `ctest --output-on-failure`, and run affected examples from the
repository root.

## 12. Project references and documentation

Our `reports/` directory contains group progress reports and module
documentation. We keep these records consistent with the current source,
build configuration, and tests.

Our implementation has no third-party plotting dependency: we calculate plot
data and generate SVG using the C++ standard library. External libraries or
publications we use as background references are not runtime dependencies
unless we explicitly add them to the build.
