# INDIVIDUAL WEEKLY PROGRESS REPORT

Project: C++ Data Visualization Library  
Module: Statistics  
Member: Ahumuza Blessing
 # Objectives
1. Implement the statistical functions defined in the Statistics header file.
2. Improve the handling of different datasets, including empty datasets and identical values.
3. Implement histogram binning and Kernel Density Estimation calculations.
4. Ensure that the statistical functions can provide results to other plotting modules.
5. Prepare the Statistics module for testing and integration.

# Activities Carried Out

1. Implemented the mean, median, variance, standard deviation, minimum, and maximum functions.
2. Added support for calculating both sample and population variance and standard deviation.
3. Implemented the `computeHistogram()` function to divide numerical data into bins and calculate their frequencies.
4. Added handling for datasets containing identical values to prevent division by zero during histogram calculations.
5. Implemented the `computeBandwidth()` function using Silverman's rule to estimate the bandwidth required for KDE calculations.
6. Implemented the `gaussianKernel()` function for calculating Gaussian density values.
7. Developed the `computeKDE()` function to generate coordinate points for smooth density curves.
8. Added checks for empty datasets and invalid parameters in several functions.

# Challenges Experienced

1. Histogram boundaries:** Ensuring that the maximum value in a dataset is included in the last histogram bin.
2. KDE calculations:** Understanding how bandwidth and Gaussian kernels work together to produce smooth density curves.
3. Special data cases:** Handling empty datasets, identical values, and insufficient data for sample variance calculations.
4. Statistical accuracy:** Distinguishing between sample and population variance when calculating data spread.

# Current Progress

The main statistical calculations, histogram binning, and KDE functions have been implemented.

The module can now calculate descriptive statistics, generate histogram bin boundaries and frequencies, and produce density coordinates for plotting.

Further testing is required to confirm the accuracy of the calculations under different input conditions.

# Work for the Next Week

1. Test the statistical functions using datasets with known results.
2. Verify histogram frequencies and bin boundaries using different datasets.
3. Test KDE calculations using different data distributions.
4. Review edge cases and improve input validation where necessary.
5. Work with the Histogram and KDE Plot module developers to integrate the statistical calculations.
6. Resolve any issues identified during integration testing.

# AI Use

AI was used to review code logic and advise accordingly.