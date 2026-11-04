
#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <cstddef>
#include <vector>

// Statistical calculations for the Data Visualization Library.
// All functions are static and do not require an object.
class Statistics {
public:
    // Existing calculations
    static std::size_t count(const std::vector<double>& data);

    static double mean(const std::vector<double>& data);

    static double minimum(const std::vector<double>& data);

    static double maximum(const std::vector<double>& data);

    static double median(std::vector<double> data);

    // Population variance (divide by N).
    static double variance(const std::vector<double>& data);

    static double standardDeviation(
        const std::vector<double>& data
    );

    // New calculations

    // Returns all values tied for the highest frequency.
    // Returns an empty vector if every value occurs once.
    static std::vector<double> mode(
        const std::vector<double>& data
    );

    // Median of the lower half of sorted data.
    static double firstQuartile(
        std::vector<double> data
    );

    // Median of the upper half of sorted data.
    static double thirdQuartile(
        std::vector<double> data
    );

    // IQR = Q3 - Q1.
    static double interquartileRange(
        const std::vector<double>& data
    );
};

#endif
