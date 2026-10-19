# Week 3 Individual Progress Report: Histogram

## NAME: SERUGYA FAHAD

## Completed

This week, I implemented the histogram calculations in `src/histogram.cpp` for the `Histogram` class. The constructor checks the input, finds the data range, creates the bin edges, and counts how many values fall into each bin. I also implemented the member functions that return the histogram's bin settings, counts, and edges.

The constructor rejects empty data, a bin count of zero, and values that are `NaN` or infinity by throwing `std::invalid_argument`. It finds the minimum and maximum with `std::minmax_element`. If all values are equal, it widens the range by 0.5 on either side so that the bins have a non-zero width.

The bin edges divide the range into equal-width intervals. The final edge is set directly to the range maximum to avoid accumulated floating-point rounding differences. The program then assigns each value to a bin and increments that bin's count. If a value produces an index equal to the number of bins, it is placed in the last bin so that the maximum value is included.

## In Progress

I am reviewing the implementation and its edge cases, especially how values at the maximum boundary and datasets with identical values are handled. The calculations are implemented, and the next step is to verify them with tests and sample data.

## Challenges/Blockers

One challenge was ensuring that a value equal to the maximum does not produce an index outside the vector of bin counts. The implementation places such a value in the final bin.

Another case was a dataset where every value is the same. Without widening the range, the bin width would be zero. The constructor widens the range in this case before calculating the bin width.

## Next Week

Next week, I will:

- Test the histogram with normal data, boundary values, and identical values.
- Check that the sum of all bin counts equals the number of input values.
- Check that the reported range, bin width, edges, and maximum count are correct.
- Review how other parts of the library will use the histogram results.

## BRIEF SUMMARY ON THE HISTOGRAM (Recap from week 2)

## What a Histogram Is and What It Is For

A histogram is a graph that shows how numerical data is distributed. It groups values into ranges called bins and records the number of values in each range. The bin counts can be used by the rest of the visualisation library to draw the bars of the chart.

## How Binning Works in My Implementation

The constructor takes a vector of numerical values and a requested number of bins. It finds the minimum and maximum values, divides the range into equal-width bins, stores the bin boundaries, and counts the values in each bin. The bin edges are stored as `numBins + 1` values because each bin has a starting and ending edge.

The counts and edges are retained in vectors. `totalCount()` adds the bin frequencies, while `maxCount()` returns the largest frequency in any bin.

## Class Structure and Organisation

### What class did I implement?

I implemented the `Histogram` class in the `dataviz` namespace. The source file defines its constructor and member functions.

### Class layout

The class layout, following the design described in my Week 2 report, is:

```text
Histogram
|-- private data
|   |-- numBins_     : number of bins
|   |-- rangeMin_    : lower end of the histogram range
|   |-- rangeMax_    : upper end of the histogram range
|   |-- binWidth_    : width of each bin
|   |-- counts_      : frequency for each bin
|   `-- binEdges_    : boundaries of the bins
`-- public functions
    |-- Histogram(data, numBins)
    |-- numBins(), rangeMin(), rangeMax(), binWidth()
    |-- totalCount(), maxCount()
    |-- counts()
    `-- binEdges()
```

- Attached is a link to the image about the class private and public members as per instructions on slack:
[Open the Week 3 histogram image](Fahad_histogram_week3.jpeg)

### Encapsulation

The class design encapsulates the histogram's stored values. The data members are private implementation details, while public member functions provide read access to the calculated results. The vector accessors return const references, so callers can inspect the counts and edges without modifying the stored vectors through those accessors. The calculation and validation are kept inside the constructor rather than requiring callers to calculate the bins themselves.

### Inheritance and Polymorphism

This implementation does not use inheritance or polymorphism. `Histogram` is implemented as a standalone class; the source contains no base class, derived class, virtual function, or override. These concepts are not needed for the current histogram calculation. The class layout drawing should therefore show `Histogram` on its own, without an inheritance relationship.

### How the class is used

The class is constructed with numerical data and a bin count. Construction validates the input and calculates the histogram. Other parts of the program can then call its public functions to obtain the range, bin width, total and maximum frequencies, bin counts, and bin edges.

## References

- Project implementation: `src/histogram.cpp`.
- NIST/SEMATECH, *Histogram* — an overview of histograms and frequency distributions:
  <https://www.itl.nist.gov/div898/handbook/eda/section3/eda33e.html>
- cppreference, *std::minmax_element* — used to find the minimum and maximum data values:
  <https://en.cppreference.com/w/cpp/algorithm/minmax_element>
