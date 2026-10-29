# Week 4 Individual Final Report: Histogram

## NAME: SERUGYA FAHAD

## Project Overview

The Data Visualization Library is a reusable C++ project for loading and preparing data, calculating statistics, and producing plots. The CMake configuration provided for the project sets C++17 as the required language standard, disables compiler-specific C++ extensions, and builds the project as one `dataviz` library.

The library target brings together the data-loading, processing, statistics, plotting, axis, annotation, rendering, and image-export modules. Its public headers are exposed from the `include` directory. The configuration also sets a default output directory at `data/output` and copies `data/input/sample.csv` into the build directory for the demonstrations.

## My Contribution: Histogram

My contribution is the histogram calculation module, declared in `include/Histogram.hpp` and implemented in `src/Histogram.cpp`. The public static function `Histogram::build` accepts a vector of numeric values and an optional bin count, defaulting to 10. It returns a vector of `HistogramBin` results.

Each `HistogramBin` contains a lower bound, an upper bound, and a count. These values are private and are exposed through the read-only `lower()`, `upper()`, and `count()` getters. Copy and move assignment are deleted so callers cannot replace a returned bin's values. `Histogram` is a friend so its `build` function can construct bins and update their counts.

The implementation rejects empty input, a zero bin count, and non-finite values (NaN and positive or negative infinity) with `std::invalid_argument`. For finite input, it finds the minimum and maximum, divides the range into equal-width bins, counts the values, and includes the maximum value in the final bin. If all values are equal, it returns one zero-width bin containing all the values.

## Integration and Examples

The CMake configuration links the histogram module into the shared `dataviz` library rather than building it as a separate library. The histogram example demonstrates how the modules work together: it loads the sample CSV, selects and converts a column, calculates histogram bins, adds a mean annotation, renders an SVG, and saves the result through the image-export module.

The configuration registers four example executables: `histogram_example` (my part), `kdeplot_example`, `countplot_example`, and `complete_library_example`. This makes the histogram one feature of the larger library rather than a standalone application.

## Testing and Build Configuration

CMake defines an individual test executable for each of the data-loading, processing, statistics, histogram, KDE, count-plot, axis, annotation, renderer, and image-export modules, plus an integration test. The test helper keeps `assert` checks enabled for both Debug and Release builds. The histogram tests cover ordinary binning, identical values, invalid bin counts, and rejection of NaN and both signs of infinity.

The standard configure, build, and test commands are:

```text
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

I verified the histogram module and its focused tests with a direct C++17 compile. The CMake configuration describes how to build and run the wider project test suite; I have not claimed that every module or integration test has passed based only on the histogram test.

## Object-Oriented Design

`Histogram` provides a public static entry point for the calculation. `HistogramBin` encapsulates its stored values with private data and const getters. The histogram implementation does not use inheritance or polymorphism; there are no base classes, derived classes, virtual functions, or overrides in these types.

## Challenges and What I Learned

A key edge case was ensuring that the maximum value is counted in the last bin rather than producing an out-of-range index. I also handled datasets containing identical values and added validation for invalid bin counts and non-finite input. Making the bin data private required updating the implementation and tests to use getters while allowing `Histogram` controlled access to construct and update bins.

Working with the CMake configuration also clarified how a reusable library, examples, input data, and module-level tests fit together. A single library target lets examples and tests use the same implementation and public headers.

## Conclusion

The histogram module now has a defined public interface, read-only bin results, input validation, and focused tests. The supplied CMake configuration places it within the wider C++17 visualization library and provides targets for examples and the project's test suite.

## References

- Project CMake configuration and histogram implementation: `CMakeLists.txt`, `include/Histogram.hpp`, and `src/Histogram.cpp`.
- NIST/SEMATECH, *Histogram*: <https://www.itl.nist.gov/div898/handbook/eda/section3/eda33e.html>
- cppreference, *std::isfinite*: <https://en.cppreference.com/w/cpp/numeric/math/isfinite>