
#include "Axis.hpp"  // Includes the Axis class declaration
#include <stdexcept>  // Provides std::invalid_argument for error handling

// Constructor: receives four values and initializes the Axis object.
Axis::Axis(
    double minValue,
    double maxValue,
    double screenStart,
    double screenEnd
)
    : minValue(minValue),       // Initializes the minimum data value
      maxValue(maxValue),       // Initializes the maximum data value
      screenStart(screenStart), // Initializes the starting drawing coordinate
      screenEnd(screenEnd) {    // Initializes the ending drawing coordinate

    // Rejects equal minimum and maximum values to prevent division by zero.
    if (minValue == maxValue) {
        throw std::invalid_argument(
            "Axis minimum and maximum cannot be equal."
        );
    }
}

// Converts a numerical value into its corresponding drawing coordinate.
double Axis::scale(double value) const {

    // Formula:
    // screenStart + [(value - minValue) / (maxValue - minValue)]
    //               * (screenEnd - screenStart)

    return screenStart +                 // Starts at the beginning of the drawing range
           (value - minValue) *          // Finds how far the value is from the minimum
           (screenEnd - screenStart) /   // Multiplies by the available drawing distance
           (maxValue - minValue);        // Divides by the total numerical range
}

// Generates evenly spaced numerical tick values.
std::vector<double> Axis::ticks(std::size_t count) const {

    // At least two tick values are required.
    if (count < 2) {
        throw std::invalid_argument(
            "Axis needs at least two tick values."
        );
    }

    std::vector<double> values; // Creates an empty vector to hold tick values
    values.reserve(count);      // Reserves memory for the requested number of ticks

    // Calculates the interval between consecutive ticks.
    // The number of intervals is one less than the number of ticks.
    double step = (maxValue - minValue) /
                  static_cast<double>(count - 1);

    // Repeats until the requested number of ticks has been generated.
    for (std::size_t i = 0; i < count; ++i) {

        // Calculates each tick and adds it to the vector.
        values.push_back(
            minValue + static_cast<double>(i) * step
        );
    }

    return values; // Returns the vector containing all generated tick values
}

// Getter: returns the minimum numerical value.
double Axis::getMin() const {
    return minValue;
}

// Getter: returns the maximum numerical value.
double Axis::getMax() const {
    return maxValue;
}

// Getter: returns the starting drawing coordinate.
double Axis::getScreenStart() const {
    return screenStart;
}

// Getter: returns the ending drawing coordinate.
double Axis::getScreenEnd() const {
    return screenEnd;
}

// Setter: changes the numerical range of an existing Axis object.
void Axis::setRange(double newMinValue, double newMaxValue) {

    // Rejects equal minimum and maximum values.
    if (newMinValue == newMaxValue) {
        throw std::invalid_argument(
            "Axis minimum and maximum cannot be equal."
        );
    }

    minValue = newMinValue; // Updates the minimum numerical value
    maxValue = newMaxValue; // Updates the maximum numerical value
}

// Setter: changes the starting and ending drawing coordinates.
void Axis::setScreenRange(
    double newScreenStart,
    double newScreenEnd
) {
    screenStart = newScreenStart; // Updates the starting drawing coordinate
    screenEnd = newScreenEnd;     // Updates the ending drawing coordinate
}
