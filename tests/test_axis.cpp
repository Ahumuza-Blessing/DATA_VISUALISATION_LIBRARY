
#include "Axis.hpp"  // Includes the Axis class
#include <cassert>    // Provides assert() for checking test conditions
#include <cmath>      // Provides std::fabs() for floating-point comparisons
#include <iostream>   // Allows messages to be printed to the console
#include <stdexcept>  // Provides exception types

int main() { // Execution begins here

    // Creates an axis with data range 0–100 and drawing range 0–500.
    Axis axis(0, 100, 0, 500);

    // Tests whether numerical values map to the correct drawing coordinates.
    // 1e-9 is a very small tolerance used when comparing decimal values.
    assert(std::fabs(axis.scale(0) - 0) < 1e-9);     // 0 maps to 0
    assert(std::fabs(axis.scale(25) - 125) < 1e-9);  // 25 maps to 125
    assert(std::fabs(axis.scale(50) - 250) < 1e-9);  // 50 maps to 250
    assert(std::fabs(axis.scale(100) - 500) < 1e-9); // 100 maps to 500

    // Generates three tick values: 0, 50, and 100.
    auto ticks = axis.ticks(3);

    assert(ticks.size() == 3); // Confirms that three ticks were generated

    // Checks that the middle tick is 50.
    assert(std::fabs(ticks[1] - 50) < 1e-9);

    // Changes the numerical range from 0–100 to -10 through 10.
    axis.setRange(-10, 10);

    // Confirms that zero maps to the middle drawing coordinate, 250.
    assert(std::fabs(axis.scale(0) - 250) < 1e-9);

    // Reverses the drawing range from 0–500 to 500–0.
    axis.setScreenRange(500, 0);

    // Confirms that -10 maps to the new starting drawing coordinate.
    assert(std::fabs(axis.scale(-10) - 500) < 1e-9);

    // Tests whether an invalid numerical range is rejected.
    bool invalidRange = false;

    try {
        Axis bad(1, 1, 0, 100); // Attempts to create an axis with equal limits
    }
    catch (const std::invalid_argument&) {
        invalidRange = true; // Records that the expected exception was caught
    }

    assert(invalidRange); // Confirms that the invalid range was rejected

    // Tests whether an invalid tick count is rejected.
    bool invalidTicks = false;

    try {
        axis.ticks(1); // Attempts to generate only one tick
    }
    catch (const std::invalid_argument&) {
        invalidTicks = true; // Records that the expected exception was caught
    }

    assert(invalidTicks); // Confirms that the invalid tick count was rejected

    // Prints a success message if all enabled assertions pass.
    std::cout << "Axis tests passed.\n";
}
