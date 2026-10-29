# Week 3 Individual Progress Report: Histogram

## NAME: SERUGYA FAHAD

## Completed

This week, I implemented the histogram calculations in `src/Histogram.cpp`. The public interface is declared in `include/Histogram.hpp`: `Histogram::build` takes a vector of values and a bin count, and returns a vector of `HistogramBin` values. Each bin contains its lower bound, upper bound, and count.

`HistogramBin` is a separate struct declared outside the `Histogram` class. Its `lower_`, `upper_`, and `count_` data members are private. Public `lower()`, `upper()`, and `count()` getter functions provide read-only access to the bin's bounds and frequency.

The function rejects empty data, a bin count of zero, and non-finite values such as `NaN` or positive and negative infinity by throwing `std::invalid_argument`. It finds the minimum and maximum with `std::min_element` and `std::max_element`. If all values are equal, it returns one zero-width bin containing all values.

Otherwise, the function divides the range into equal-width bins and sets the upper bound of the final bin directly to the maximum value. Each value is assigned to a bin and increments its count. If the calculated index is at or beyond the bin count, it is clamped to the last bin so the maximum value is included.

## In Progress

I tested the implementation with ordinary data, identical values, a zero bin count, and non-finite values. The checks confirmed the bin counts and bounds, and that `std::invalid_argument` is thrown for a zero bin count, `NaN`, and both positive and negative infinity. Compile-time checks also confirm that `HistogramBin` cannot be copy- or move-assigned.

## Challenges/Blockers

One challenge was ensuring that a value equal to the maximum does not produce an index outside the vector of bin counts. The implementation places such a value in the final bin.

Another case was a dataset where every value is the same. The implementation handles it separately by returning one zero-width bin containing every value.

## Next Steps

The next step is to integrate the returned bins with the library's visualization components and review the histogram API as those components are developed.

## BRIEF SUMMARY ON THE HISTOGRAM (Recap from week 2)

## What a Histogram Is and What It Is For

A histogram is a graph that shows how numerical data is distributed. It groups values into ranges called bins and records the number of values in each range. The bin counts can be used by the rest of the visualisation library to draw the bars of the chart.

## How Binning Works in My Implementation

`Histogram::build` takes a vector of numerical values and a requested number of bins. It finds the minimum and maximum values, divides the range into equal-width bins, and counts the values in each bin. The returned vector has one `HistogramBin` per bin, with each bin carrying its own lower and upper bounds.

The counts and bounds are returned in the bins; the caller can inspect or aggregate them as needed.

## Class Structure and Organisation

### What class did I implement?

I implemented the global `Histogram` class interface declared in `include/Histogram.hpp`. The source file `src/Histogram.cpp` defines its static `build` function.

### Class layout

The header declares a standalone `HistogramBin` struct and a separate `Histogram` class. In this diagram, `+` means public and `-` means private; neither type has protected (`#`) members:

```text
HistogramBin struct
+ lower() const -> double
+ upper() const -> double
+ count() const -> std::size_t
+ copy/move constructors
+ copy/move assignment = delete
- HistogramBin(lower, upper, count) [friend: Histogram]
- double lower_
- double upper_
- std::size_t count_

Histogram
+ static build(data, binCount) -> vector<HistogramBin>
```

![Histogram API class and struct diagram](./Fahad_histogram_week3_class_diagram.jpeg)

The digital diagram is a guide to the layout. The assignment asks me to draw the layout on paper, take a clear photo, and upload that photo alongside this report.

### Access Specifiers and Encapsulation

`Histogram` explicitly marks `build` as `public` and has no private or protected members. Although `HistogramBin` is declared with `struct`, its stored values are in a `private` section. Its public `const` getters allow inspection without mutation; there are no setters, and copy/move assignment operators are deleted. `Histogram` is a friend so its `build` function can construct and count bins. This encapsulates each bin's values while returning bins by value.

### Inheritance and Polymorphism

This implementation does not use inheritance or polymorphism. `Histogram` is a standalone class, and `HistogramBin` is a separate struct; neither inherits from nor is a base class for another type. There are no virtual functions or overrides. These concepts are not used in the current histogram implementation.

### How the class is used

The function is called with numerical data and a bin count. It validates the supported input conditions and calculates the bins. Other parts of the program can then use each returned bin's bounds and frequency.

## References

- Public interface: `include/Histogram.hpp`.
- Project implementation: `src/Histogram.cpp`.
- NIST/SEMATECH, *Histogram* — an overview of histograms and frequency distributions:
  <https://www.itl.nist.gov/div898/handbook/eda/section3/eda33e.html>
- cppreference, *std::min_element* and *std::max_element* — used to find the minimum and maximum data values:
  <https://en.cppreference.com/w/cpp/algorithm/min_element>
