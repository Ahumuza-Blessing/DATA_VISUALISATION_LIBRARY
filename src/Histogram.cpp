#include "Histogram.hpp" // Declares Histogram and HistogramBin.

#include <algorithm> // Finds the data range.
#include <cmath> // Checks whether values are finite.
#include <stdexcept> // Reports invalid histogram input.

// Implements histogram bin construction and value counting.

// Validates the input, creates equally sized bins across its range, and
// counts the values assigned to each bin.
std::vector<HistogramBin> Histogram::build( // Defines the histogram-construction operation.
    const std::vector<double>& data, // Receives the values to place into bins.
    std::size_t binCount // Receives the requested number of bins.
) { // Begins histogram construction.
    if (data.empty()) { // Rejects a dataset with no observations.
        throw std::invalid_argument("Histogram requires at least one data value."); // Reports missing data.
    } // Ends the empty-input check.

    if (binCount == 0) { // Rejects a request that cannot create any bins.
        throw std::invalid_argument("Histogram bin count must be greater than zero."); // Reports invalid bin count.
    } // Ends the bin-count check.

    // Non-finite values make range and bin-index calculations unreliable.
    for (double value : data) { // Checks every observation before range calculations.
        if (!std::isfinite(value)) { // Detects NaN and positive or negative infinity.
            throw std::invalid_argument("Histogram values must be finite."); // Rejects a non-finite observation.
        } // Ends the finite-value check.
    } // Ends validation of all observations.

    double minValue = *std::min_element(data.begin(), data.end()); // Finds the smallest observation.
    double maxValue = *std::max_element(data.begin(), data.end()); // Finds the largest observation.

    if (minValue == maxValue) { // Handles data whose observations are all identical.
        std::vector<HistogramBin> bins; // Creates the result collection.
        bins.push_back(HistogramBin(minValue, maxValue, data.size())); // Places every observation in one zero-width bin.
        return bins; // Returns the single populated bin.
    } // Ends the constant-data case.

    double binWidth = (maxValue - minValue) / static_cast<double>(binCount); // Computes the equal interval width.

    std::vector<HistogramBin> bins; // Creates the collection that will hold each bin.
    bins.reserve(binCount); // Allocates space for the requested number of bins.

    for (std::size_t i = 0; i < binCount; ++i) { // Creates each interval from left to right.
        double lower = minValue + static_cast<double>(i) * binWidth; // Calculates this interval's lower edge.
        double upper = (i == binCount - 1) // Checks whether this is the final interval.
            ? maxValue // Uses the data maximum as the last upper edge.
            : minValue + static_cast<double>(i + 1) * binWidth; // Otherwise calculates the next interval boundary.

        bins.push_back(HistogramBin(lower, upper, 0)); // Adds the new empty bin.
    } // Ends bin creation.

    // A value on the final boundary must still count in the last bin.
    for (double value : data) { // Assigns each observation to a bin.
        std::size_t index = static_cast<std::size_t>( // Converts the range position to a bin index.
            (value - minValue) / binWidth // Measures how many bin widths separate value from the minimum.
        ); // Completes the bin-index calculation.

        if (index >= binCount) { // Handles values at the maximum boundary.
            index = binCount - 1; // Places the boundary value in the final bin.
        } // Ends the upper-bound correction.

        // Histogram is a friend of HistogramBin, so it can update the private count.
        ++bins[index].count_; // Adds this observation to its selected bin's frequency.
    } // Ends observation counting.

    return bins; // Returns the completed bins to the caller.
} // Ends Histogram::build.
