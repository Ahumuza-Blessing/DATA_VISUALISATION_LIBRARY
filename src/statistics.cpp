#include "Statistics.hpp"
#include <numeric>
#include <algorithm>
#include <cmath>

double Statistics::mean(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / static_cast<double>(data.size());
}

double Statistics::median(std::vector<double> data) {
    if (data.empty()) return 0.0;

    std::sort(data.begin(), data.end());
    size_t n = data.size();

    if (n % 2 != 0) {
        return data[n / 2];
    }
    return (data[(n - 1) / 2] + data[n / 2]) / 2.0;
}

double Statistics::variance(const std::vector<double>& data, bool sample) {
    if (data.empty() || (sample && data.size() <= 1)) return 0.0;

    double avg = mean(data);
    double sum_sq = 0.0;
    for (double val : data) {
        double diff = val - avg;
        sum_sq += diff * diff;
    }

    size_t divisor = sample ? (data.size() - 1) : data.size();
    return sum_sq / static_cast<double>(divisor);
}

double Statistics::standardDeviation(const std::vector<double>& data, bool sample) {
    return std::sqrt(variance(data, sample));
}

double Statistics::min(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    return *std::min_element(data.begin(), data.end());
}

double Statistics::max(const std::vector<double>& data) {
    if (data.empty()) return 0.0;
    return *std::max_element(data.begin(), data.end());
}

Statistics::HistogramBins Statistics::computeHistogram(const std::vector<double>& data, int numBins) {
    HistogramBins result;
    if (data.empty() || numBins <= 0) return result;

    double low = min(data);
    double high = max(data);

    // Prevent divide-by-zero if all values in data are identical
    if (low == high) {
        high += 1.0;
    }

    double binWidth = (high - low) / numBins;

    result.edges.resize(numBins + 1);
    result.counts.assign(numBins, 0);

    for (int i = 0; i <= numBins; ++i) {
        result.edges[i] = low + i * binWidth;
    }

    for (double val : data) {
        int index = static_cast<int>((val - low) / binWidth);
        if (index >= numBins) {
            index = numBins - 1; // Include upper boundary in last bin
        }
        if (index >= 0) {
            result.counts[index]++;
        }
    }

    return result;
}

double Statistics::computeBandwidth(const std::vector<double>& data) {
    if (data.size() < 2) return 1.0;

    double stdDev = standardDeviation(data, true);
    if (stdDev == 0.0) stdDev = 1.0;

    // Silverman's rule: h = 0.9 * stdDev * n^(-1/5)
    return 0.9 * stdDev * std::pow(static_cast<double>(data.size()), -0.2);
}

double Statistics::gaussianKernel(double x, double xi, double bandwidth) {
    if (bandwidth <= 0.0) return 0.0;

    double u = (x - xi) / bandwidth;
    const double invSqrt2Pi = 0.3989422804014327; // 1 / sqrt(2 * PI)

    return (invSqrt2Pi / bandwidth) * std::exp(-0.5 * u * u);
}

std::vector<std::pair<double, double>> Statistics::computeKDE(const std::vector<double>& data, int numPoints) {
    std::vector<std::pair<double, double>> points;
    if (data.empty() || numPoints <= 0) return points;

    double low = min(data);
    double high = max(data);

    // Expand bounds slightly so curves taper off smoothly on both ends
    double margin = (high - low) * 0.1;
    if (margin == 0.0) margin = 1.0;

    double start = low - margin;
    double end = high + margin;
    double step = (end - start) / (numPoints - 1);

    double h = computeBandwidth(data);

    for (int i = 0; i < numPoints; ++i) {
        double currentX = start + i * step;
        double sumDensity = 0.0;

        for (double val : data) {
            sumDensity += gaussianKernel(currentX, val, h);
        }

        double finalDensity = sumDensity / static_cast<double>(data.size());
        points.push_back({currentX, finalDensity});
    }

    return points;
}