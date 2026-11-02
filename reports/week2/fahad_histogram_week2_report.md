# Week 2 Individual Progress Report: Histogram

## NAME: SERUGYA FAHAD

## Completed

This week, I worked on the histogram component of the data visualisation library and drafted the `Histogram` class design. The checked-in interface is now in `include/Histogram.hpp`.

The design was later simplified from a stateful class to a static builder. The header declares `HistogramBin`, which stores a bin's lower bound, upper bound, and count, and `Histogram::build`, which returns a vector of bins. Its implementation is in `src/Histogram.cpp`.

## In Progress

I am reviewing the binning behavior and its edge cases. The implementation in `src/Histogram.cpp` validates empty input and a zero bin count, finds the data minimum and maximum, and calculates bin boundaries and counts.

## Challenges/Blockers

One issue is making sure values on the boundaries of bins are counted correctly. `Histogram::build` assigns values using their offset from the minimum and the bin width.

The largest value is included in the final bin, including when its calculated index reaches the number of bins.

The function rejects empty data, a bin count of zero, and non-finite values such as `NaN` or positive and negative infinity by throwing `std::invalid_argument`.

## Next Week

Next week, I will continue implementing and testing `Histogram::build` in `src/Histogram.cpp`, using the interface in `include/Histogram.hpp`.

I will write the code for:

- Finding the minimum and maximum values in the dataset.
- Calculating the width of each bin.
- Creating each bin's lower and upper bounds.
- Counting how many values fall into each bin.
- Returning the bins and their counts.
- Testing the class with sample numerical data.

## BRIEF SUMMARY ON THE HISTOGRAM

## What a Histogram Is and What It Is For

A histogram is a graph that shows how numerical data is distributed. It groups values into ranges called bins instead of displaying every value separately.

For example, if a dataset contains student marks, a histogram can show how many students scored between 40–49, 50–59, 60–69, and other ranges. This helps users see where most values are grouped, how spread out the data is, and whether there are unusual values.

## How Binning Works

Binning means dividing the data range into smaller intervals. Each value is placed in the bin whose range contains it.

For example, if the data ranges from 0 to 100 and there are 10 bins, the data can be divided into equal ranges. The program then counts how many values are found in each range. These counts are used to create the bars of the histogram.

## Class Structure and Organisation

### What class did I create?

I created one class called `Histogram`.

### Why did I create this class?

I created the `Histogram` class to keep the binning calculation in one place. Its `build` function divides numerical data into bins and returns their frequencies.

This makes the program more organised because other parts of the project do not need to perform the binning calculations themselves.

### What is the `HistogramBin` struct?

In `include/Histogram.hpp`, `struct HistogramBin` defines the data returned for one histogram bin. Although struct members are public by default in C++, this struct explicitly declares its stored values private:

- `lower_` stores the bin's lower bound and is read through `lower()`.
- `upper_` stores the bin's upper bound and is read through `upper()`.
- `count_` stores how many input values were assigned to the bin and is read through `count()`.

These getters are `const`, and there are no setters. Copy and move assignment are deleted, so callers cannot replace one bin's value with another. `Histogram::build` returns a `std::vector<HistogramBin>`, so each element represents one bin whose values can be inspected but not changed through the public interface.

### What function performs the calculation?

`Histogram::build(const std::vector<double>& data, std::size_t binCount)` is declared in `include/Histogram.hpp` and implemented in `src/Histogram.cpp`. It returns a `std::vector<HistogramBin>`. The bin count defaults to 10 when the caller does not provide one.

### Why does the current interface return bins?

The interface returns calculated bins directly rather than keeping histogram state on a `Histogram` object. Callers can inspect a returned bin using `lower()`, `upper()`, and `count()`, but cannot modify its stored values.

### How will the class be used in the program?

The rest of the program calls `Histogram::build(data, binCount)` and uses the returned bins to obtain the bounds and frequency counts needed to display the histogram.

## References

- What is a histogram and what is it for?
<https://www.geeksforgeeks.org/maths/histogram/>

- How does binning work?
 <https://fastercapital.com/content/Data-Binning--Data-Binning--The-Key-to-Structured-Histograms.html>

- Class structure and organisation.
 <https://stackoverflow.com/questions/49792877/build-a-histogram-with-a-predefined-number-of-bins-in-c>
