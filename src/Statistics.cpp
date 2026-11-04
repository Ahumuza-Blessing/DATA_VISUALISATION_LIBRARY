
#include "Statistics.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <stdexcept>

namespace {

// Reject empty datasets.
void ensureNotEmpty(const std::vector<double>& data) {
    if (data.empty()) {
        throw std::invalid_argument(
            "Statistics cannot be calculated for empty data."
        );
    }
}

// Reject NaN and infinity.
void validateData(const std::vector<double>& data) {
    ensureNotEmpty(data);

    for (double value : data) {
        if (!std::isfinite(value)) {
            throw std::invalid_argument(
                "Statistics requires finite numerical values."
            );
        }
    }
}

// Calculate median over a nonempty, sorted range [begin, end).
double medianOfSortedRange(
    const std::vector<double>& sorted,
    std::size_t begin,
    std::size_t end
) {
    const std::size_t length = end - begin;
    const std::size_t middle = begin + length / 2;

    if (length % 2 == 0) {
        return sorted[middle - 1] / 2.0 +
               sorted[middle] / 2.0;
    }

    return sorted[middle];
}

// Calculate both quartiles with the median-of-halves method.
std::pair<double, double> calculateQuartiles(
    std::vector<double> data
) {
    validateData(data);

    std::sort(data.begin(), data.end());

    // A single value is both quartiles.
    if (data.size() == 1) {
        return {data[0], data[0]};
    }

    const std::size_t middle = data.size() / 2;

    // For odd datasets, exclude the central value.
    const std::size_t upperStart =
        middle + (data.size() % 2);

    const double q1 = medianOfSortedRange(
        data, 0, middle
    );

    const double q3 = medianOfSortedRange(
        data, upperStart, data.size()
    );

    return {q1, q3};
}

} // namespace

// =====================================================
// EXISTING CALCULATIONS
// =====================================================

std::size_t Statistics::count(
    const std::vector<double>& data
) {
    return data.size();
}

double Statistics::mean(
    const std::vector<double>& data
) {
    validateData(data);

    const double total = std::accumulate(
        data.begin(), data.end(), 0.0
    );

    return total / static_cast<double>(data.size());
}

double Statistics::minimum(
    const std::vector<double>& data
) {
    validateData(data);

    return *std::min_element(
        data.begin(), data.end()
    );
}

double Statistics::maximum(
    const std::vector<double>& data
) {
    validateData(data);

    return *std::max_element(
        data.begin(), data.end()
    );
}

double Statistics::median(
    std::vector<double> data
) {
    validateData(data);

    // Sort a copy without changing the original dataset.
    std::sort(data.begin(), data.end());

    return medianOfSortedRange(
        data, 0, data.size()
    );
}

double Statistics::variance(
    const std::vector<double>& data
) {
    validateData(data);

    const double average = mean(data);
    double totalSquaredDifference = 0.0;

    for (double value : data) {
        const double difference = value - average;

        totalSquaredDifference +=
            difference * difference;
    }

    // Population variance: divide by N, not N - 1.
    return totalSquaredDifference /
           static_cast<double>(data.size());
}

double Statistics::standardDeviation(
    const std::vector<double>& data
) {
    return std::sqrt(variance(data));
}

// =====================================================
// NEW CALCULATIONS
// =====================================================

// MODE
std::vector<double> Statistics::mode(
    const std::vector<double>& data
) {
    validateData(data);

    std::map<double, std::size_t> frequencies;

    for (double value : data) {
        ++frequencies[value];
    }

    std::size_t highestFrequency = 0;

    for (const auto& entry : frequencies) {
        highestFrequency = std::max(
            highestFrequency, entry.second
        );
    }

    // If every value occurs once, there is no mode.
    if (highestFrequency == 1) {
        return {};
    }

    std::vector<double> modes;

    for (const auto& entry : frequencies) {
        if (entry.second == highestFrequency) {
            modes.push_back(entry.first);
        }
    }

    return modes;
}

// FIRST QUARTILE (Q1)
double Statistics::firstQuartile(
    std::vector<double> data
) {
    return calculateQuartiles(data).first;
}

// THIRD QUARTILE (Q3)
double Statistics::thirdQuartile(
    std::vector<double> data
) {
    return calculateQuartiles(data).second;
}

// INTERQUARTILE RANGE
double Statistics::interquartileRange(
    const std::vector<double>& data
) {
    const auto quartiles = calculateQuartiles(data);

    return quartiles.second - quartiles.first;
}
