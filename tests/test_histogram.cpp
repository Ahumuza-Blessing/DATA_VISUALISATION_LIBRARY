#include "Histogram.hpp" // Provides the histogram API and bin type.

#include <cassert> // Checks expected bin values and errors.
#include <iostream> // Prints the test result.
#include <limits> // Supplies NaN and infinity test values.
#include <stdexcept> // Identifies invalid-input exceptions.
#include <type_traits> // Checks HistogramBin assignment properties.

// Exercises bin construction, value counting, and invalid-input handling.
int main() { // Starts the histogram test program.
    static_assert(!std::is_copy_assignable_v<HistogramBin>); // Confirms bins cannot be copy-assigned.
    static_assert(!std::is_move_assignable_v<HistogramBin>); // Confirms bins cannot be move-assigned.

    // Values are counted in two equal-width bins.
    auto bins = Histogram::build({1, 2, 3, 4}, 2); // Builds two bins for four observations.
    assert(bins.size() == 2); // Verifies the requested number of bins was created.
    assert(bins[0].count() == 2 && bins[1].count() == 2); // Verifies each bin contains two observations.
    assert(bins[0].lower() == 1 && bins[0].upper() == 2.5); // Verifies the first bin's boundaries.

    // A constant dataset produces one bin containing every value.
    auto same = Histogram::build({5, 5, 5}, 4); // Builds a histogram from identical values.
    assert(same.size() == 1 && same[0].count() == 3); // Verifies one bin contains all observations.
    assert(same[0].lower() == 5 && same[0].upper() == 5); // Verifies the constant bin has zero width.

    // A zero bin count is rejected.
    bool threw = false; // Tracks whether invalid input raised an exception.
    try { Histogram::build({1, 2}, 0); } // Attempts to build with no bins.
    catch (const std::invalid_argument&) { threw = true; } // Records the expected validation error.
    assert(threw); // Confirms zero bins were rejected.

    // Reject NaN and both signs of infinity before calculating bins.
    threw = false; // Resets the exception flag for the NaN case.
    try { Histogram::build({1, std::numeric_limits<double>::quiet_NaN()}, 2); } // Supplies a NaN observation.
    catch (const std::invalid_argument&) { threw = true; } // Records rejection of NaN.
    assert(threw); // Confirms NaN was rejected.

    threw = false; // Resets the exception flag for positive infinity.
    try { Histogram::build({1, std::numeric_limits<double>::infinity()}, 2); } // Supplies positive infinity.
    catch (const std::invalid_argument&) { threw = true; } // Records rejection of positive infinity.
    assert(threw); // Confirms positive infinity was rejected.

    threw = false; // Resets the exception flag for negative infinity.
    try { Histogram::build({1, -std::numeric_limits<double>::infinity()}, 2); } // Supplies negative infinity.
    catch (const std::invalid_argument&) { threw = true; } // Records rejection of negative infinity.
    assert(threw); // Confirms negative infinity was rejected.

    std::cout << "Histogram tests passed.\n"; // Prints confirmation after all assertions pass.
    return 0; // Signals that every histogram test completed successfully.
} // Ends the histogram test program.