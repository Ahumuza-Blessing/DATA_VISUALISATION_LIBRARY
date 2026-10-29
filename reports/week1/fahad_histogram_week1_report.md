
# Individual Week 1 Progress Report: Histogram

## NAME: SERUGYA FAHAD

## Completed

- During Week 1, I participated in the group discussion about the project requirements, system structure, and expected visualisations. I was assigned responsibility for the histogram component of the data visualisation library.

- My focus was to understand the purpose of a histogram and how it differs from other chart types. A histogram will be used to show the distribution of numerical data by grouping values into intervals, known as bins. I also considered the main elements required for the visualisation, including the dataset, bin ranges, frequency counts, axis labels, title, and colours.

- I discussed how the histogram feature should fit into the agreed project structure and identified the work I will carry out in the following weeks: preparing sample numerical data, designing the histogram layout, implementing the chart, and testing that the bins and frequencies are displayed correctly.

## In Progress

- Planning the Histogram class structure.
- Identifying the data, bins, labels, and frequency calculations required for the histogram.

## Challenges/Blockers

- Determining the most suitable method for grouping numerical values into bins.
- Understanding how the histogram should handle different data ranges and bin sizes.

## Next Week

- Design and create the `include/Histogram.hpp` file.
- Define the Histogram class, its attributes, and its main methods.
- Begin implementing the binning and frequency-counting logic.

## What a histogram is and what it is for

- A histogram is a graph that shows how numerical data is distributed across a range of values.
- It groups values into intervals called bins and displays the number of values in each bin.
- It is useful for identifying patterns such as common values, spread, gaps, and unusual values in a dataset.

## How binning works (my understanding)

- Binning divides a range of numerical values into equal or chosen intervals.
- Each data value is placed into the bin whose range contains that value.
- The histogram counts how many values fall into each bin.
- The height of each bar represents the frequency of values within that bin.

## Initial planned design for the Histogram class

- The initial plan was for the class to store numerical data and histogram settings.
- The implementation was later simplified: `include/Histogram.hpp` now declares a `HistogramBin` type and a static `Histogram::build` function.
- `Histogram::build` returns each bin's lower bound, upper bound, and frequency; the implementation is in `src/Histogram.cpp`.

## AI Use

- Tool: ChatGPT/Codex
- Purpose: To explain histogram concepts, binning, and possible class design.
- Reason: To improve my understanding of the required visualisation before implementation.

## Conclusion

This week mainly involved planning, understanding my assigned role, and preparing to begin implementation of the histogram component.

## References

1. NIST/SEMATECH. Histogram. Explains a histogram’s purpose, frequency counts, and grouping data into equal-sized bins.
<https://www.itl.nist.gov/div898/handbook/eda/section3/eda33e.html>

2. NIST/SEMATECH. Histogram Class Width. Discusses bin/class-width selection and why it affects the resulting histogram.
<https://www.itl.nist.gov/div898/software/dataplot/refman1/auxillar/histwidt.html>

3. cppreference. C++ Standard Library <vector>, used by the interface in `include/Histogram.hpp`.
<https://en.cppreference.com/w/cpp/header/vector>
