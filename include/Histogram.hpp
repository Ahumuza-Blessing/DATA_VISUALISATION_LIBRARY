#ifndef HISTOGRAM_HPP // Starts the include guard for this header.
#define HISTOGRAM_HPP // Prevents duplicate declarations from repeated inclusion.

#include <cstddef> // Provides std::size_t for bin counts.
#include <vector> // Stores the input values and resulting bins.

// Defines histogram bins and the API for grouping numeric data into bins.

// A histogram divides numerical values into groups called bins.
// Each bin stores its lower limit, upper limit, and number of values.
struct HistogramBin { // Represents the boundaries and count of one histogram interval.
public: // Exposes the bin's supported construction and read-only accessors.
    // Copies a bin's boundaries and count.
    HistogramBin(const HistogramBin&) = default; // Allows a bin to be copied.

    // Transfers a bin's boundaries and count.
    HistogramBin(HistogramBin&&) noexcept = default; // Allows a bin to be moved without throwing.

    // Prevents assigning over an existing bin.
    HistogramBin& operator=(const HistogramBin&) = delete; // Keeps a bin's stored identity fixed.

    // Prevents move-assigning over an existing bin.
    HistogramBin& operator=(HistogramBin&&) = delete; // Disallows replacing a bin by move assignment.

    // Returns the lower edge of the bin.
    double lower() const noexcept { return lower_; } // Reads the inclusive lower boundary.

    // Returns the upper edge of the bin.
    double upper() const noexcept { return upper_; } // Reads the upper boundary.

    // Returns the number of values assigned to the bin.
    std::size_t count() const noexcept { return count_; } // Reads the bin's accumulated frequency.

private: // Keeps bin state and direct construction internal.
    friend class Histogram; // Lets the builder create bins and increment their counts.

    // Creates a bin with the given boundaries and initial count.
    HistogramBin(double lower, double upper, std::size_t count)
        : lower_(lower), upper_(upper), count_(count) {} // Initializes all three stored properties.

    double lower_; // Stores this bin's lower boundary.
    double upper_; // Stores this bin's upper boundary.
    std::size_t count_; // Stores the number of assigned data values.
}; // Completes the histogram-bin value type.

class Histogram { // Provides static operations for building histograms.
public: // Makes the histogram builder available to callers.
    // Divides finite data into equally sized bins and returns each bin's
    // boundaries and value count.
    static std::vector<HistogramBin> build( // Builds bins and returns their boundaries and counts.
        const std::vector<double>& data, // Supplies the numeric observations to group.
        std::size_t binCount = 10 // Sets the requested number of equal-width bins.
    ); // Completes the builder declaration.
}; // Completes the static histogram API.

#endif // Ends the include guard.
