#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>
#include <utility>

class Statistics {
public:
    // Structure to hold histogram results (edges and frequency counts)
    struct HistogramBins {
        std::vector<double> edges;
        std::vector<int> counts;
    };

    // 1. Basic Descriptive Math Functions
    static double mean(const std::vector<double>& data);
    static double median(std::vector<double> data); // Passed by value to safely sort
    static double variance(const std::vector<double>& data, bool sample = true);
    static double standardDeviation(const std::vector<double>& data, bool sample = true);
    static double min(const std::vector<double>& data);
    static double max(const std::vector<double>& data);

    // 2. Histogram Helper (Binning)
    static HistogramBins computeHistogram(const std::vector<double>& data, int numBins = 10);

    // 3. Smooth Density Curves (Kernel Density Estimation)
    static double computeBandwidth(const std::vector<double>& data); // Silverman's Rule
    static double gaussianKernel(double x, double xi, double bandwidth);
    static std::vector<std::pair<double, double>> computeKDE(const std::vector<double>& data, int numPoints = 100);
};

#endif // STATISTICS_HPP