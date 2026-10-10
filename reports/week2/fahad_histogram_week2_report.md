# Week 2 Individual Progress Report: Histogram

## NAME: SERUGYA FAHAD

## Completed

This week, I worked on the histogram component of the data visualisation library. I created the `histogram.hpp` file and declared one class called `Histogram` inside the `dataviz` namespace.

The header file contains the class structure. It shows the data the class will store and the functions that will later be implemented in the `.cpp` file.

## In Progress

I am reviewing the design of the `Histogram` class and preparing to implement its functions. At this stage, the class has been declared in the header file (histogram.hpp), but the function definitions have not yet been written in cpp source/implementation file (histogram.cpp).

## Challenges/Blockers

One issue I considered was how to make sure values on the boundaries of bins are counted correctly. The class design solves this by using bin ranges in the form `[edges[i], edges[i+1])`. This means a value is included at the start of a bin but not normally at the end.

The final bin includes its upper edge so that the largest value in the dataset is included.

I also considered invalid input. The constructor is designed to reject empty data, zero bins, and invalid numbers such as `NaN (Not a valid Number)` or infinity.

## Next Week

Next week, I will create the `histogram.cpp` file and implement the functions declared in `histogram.hpp`.

I will write the code for:

- Finding the minimum and maximum values in the dataset.
- Calculating the width of each bin.
- Creating the bin edges.
- Counting how many values fall into each bin.
- Returning the total number of values and the highest bin count.
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

I created the `Histogram` class to keep all histogram-related work in one place. The class will handle numerical data, divide the data into bins, and store the frequency of values in each bin.

This makes the program more organised because other parts of the project do not need to perform the binning calculations themselves.

### What data does the class hold?

The `Histogram` class has the following private data members:

- `numBins_` stores the number of bins.
- `rangeMin_` stores the smallest value in the dataset.
- `rangeMax_` stores the largest value in the dataset.
- `binWidth_` stores the width of each bin.
- `counts_` stores the number of values in each bin.
- `binEdges_` stores the boundaries of the bins.

### What functions operate on the data?

The class has a constructor:

- `Histogram(const std::vector<double>& data, std::size_t numBins)`

The constructor receives the numerical data and the number of bins.

The class also has public member functions:

- `numBins()` returns the number of bins.
- `rangeMin()` returns the minimum value.
- `rangeMax()` returns the maximum value.
- `binWidth()` returns the width of each bin.
- `totalCount()` returns the total number of values processed.
- `maxCount()` returns the highest frequency in any bin.
- `counts()` returns the frequency counts.
- `binEdges()` returns the bin boundaries.

These functions are declared in the header file and will be implemented in `histogram.cpp` next week.

### Why are some members private and others public?

The data members are private because they are internal details of the class. Other parts of the program should not change them directly, because this could lead to incorrect histogram results.

The member functions are public because they allow other parts of the program to safely access histogram information. For example, another part of the visualisation library can call `counts()` to get the bin frequencies without changing the stored data.

### How will the class be used in the program?

The rest of the program will create a `Histogram` object by giving it numerical data and a number of bins. The class will then calculate the histogram information. Other parts of the project can use the public functions to obtain the bin edges, frequency counts, and other results needed to display the histogram.

## References

- What is a histogram and what is it for?
<https://www.geeksforgeeks.org/maths/histogram/>

- How does binning work?
 <https://fastercapital.com/content/Data-Binning--Data-Binning--The-Key-to-Structured-Histograms.html>

- Class structure and organisation.
 <https://stackoverflow.com/questions/49792877/build-a-histogram-with-a-predefined-number-of-bins-in-c>
