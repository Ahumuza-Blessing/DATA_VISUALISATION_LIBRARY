Individual Report: The Statistics Module
Name: Ahumuza Blessing
Module: Statistics.hpp and Statistics.cpp
Objectives
1.	To provide Mathematical Support: Build a clean math module that calculates all necessary values for data analysis and visualization.
2.	To Support Statistical Plots: Supply ready to use math routines for drawing histograms (binning) and smooth density curves (KDE).
3.	To maintain Self-Containment: Implement all formulas from scratch using standard C++ to keep the library lightweight and free of external dependencies.
4.	Keep Code Modular: Keep mathematical logic separated from file loading and visual drawing so other team members can easily integrate it into their modules.

Overview
The Statistics module is the math engine of our C++ visualization library. While other parts of our project read files or draw shapes on the screen this module handles all the calculations needed to make charts like finding averages, grouping data into histogram bins, and calculating smooth curves for density plots.

 What Was Built
A.	Basic Math Functions
I built functions to give a quick summary of any list of numbers:
 * Mean: Calculates the average value.
 * Median: Finds the middle number in the dataset.
 * Variance & Standard Deviation: Measures how spread out the numbers are.
 * Min & Max: Finds the smallest and largest values in the data.
B. Histogram Helper (compute Histogram)
To help draw histograms (bar charts for continuous numbers), this function:
 * Splits the range between the lowest and highest number into equal sections (bins).
 * Counts how many data points fall into each section.
 * Returns the bin boundaries and count values so the plot module can easily draw the bars.
C. Smooth Density Curves (compute KDE)
For Kernel Density Estimation (KDE) plots, which show a smooth curve instead of bars:
 * Bandwidth: Automatically figures out how smooth the curve should be based on data spread and sample size 
 * Gaussian Kernel: Turns each number into a smooth bell-shaped curve.
 * Coordinates: Combines those curves to create (x, y) graph coordinates that can be drawn on screen.

 Why It Was Designed This Way
 * Easy to Use: All functions are static, meaning other team members can call 
Statistics: mean() directly without setting up complex objects.
 * Safe Data Handling: Sorting or calculating numbers won't mess up or change the original raw data.
 * Clean Teamwork: Keeping the math logic in Statistics.cpp keeps the plot code simple, so team members working on charts can focus only on drawing.
 
Summary
The Statistics module is complete and ready to use. It provides all the necessary math so that modules like Histogram and KDE Plot can easily get their numbers and draw clear charts.