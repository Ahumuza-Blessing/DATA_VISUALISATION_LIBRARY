#include "Axis.hpp"

#include <stdexcept>

using namespace std;

// Axis controls how values are placed on the graph
// So I need the minimum and maximum values of the actual data
// I also need the starting and ending positions where the axis will be drawn

Axis::Axis(
    double minValue,
    double maxValue,
    double screenStart,
    double screenEnd
)
    : minValue(minValue),
      maxValue(maxValue),
      screenStart(screenStart),
      screenEnd(screenEnd) {

    // The minimum and maximum values should not be equal
    // because there would be no range to calculate the scale from
    if (minValue == maxValue) {
        throw invalid_argument("Axis minimum and maximum cannot be equal!");
    }
}


// Scaling function
// This should receive an actual data value
// then convert it to the correct position on the graph
// For example, if the data range is 0 to 100
// and the screen range is 0 to 500,
// then a value of 50 should be placed around position 250

double Axis::scale(double value) const {

    // I first find how far the value is from the minimum
    // then compare that with the whole data range
    // after that I fit it into the available screen range

    return screenStart +
           (value - minValue) *
           (screenEnd - screenStart) /
           (maxValue - minValue);
}


// Tick function
// Ticks are the values/divisions that appear along the axis
// For example: 0, 20, 40, 60, 80, 100
// So I need to know how many tick values I want

vector<double> Axis::ticks(size_t count) const {

    // An axis needs at least two tick values
    // because we need a starting and ending value
    if (count < 2) {
        throw invalid_argument("Axis needs at least two tick values.");
    }

    // I create a vector where all the calculated tick values will be stored
    vector<double> values;

    // Reserve enough space for the number of ticks required
    values.reserve(count);

    // Calculate the distance between one tick and the next
    // Example: for 0 to 100 with 6 ticks,
    // step = (100 - 0) / (6 - 1) = 20

    double step = (maxValue - minValue) /
                  static_cast<double>(count - 1);

    // Start from the minimum value
    // then keep adding the step until all tick values are created

    for (size_t i = 0; i < count; ++i) {
        values.push_back(
            minValue + static_cast<double>(i) * step
        );
    }

    // Return all the calculated tick values
    return values;
}


// These functions allow other parts of the library
// to read the minimum and maximum values of the axis

double Axis::getMin() const {
    return minValue;
}

double Axis::getMax() const {
    return maxValue;
}


// These functions return the positions where the axis starts and ends
// on the drawing area

double Axis::getScreenStart() const {
    return screenStart;
}

double Axis::getScreenEnd() const {
    return screenEnd;
}


// This function allows the data range to be changed later
// without creating another Axis object

void Axis::setRange(double newMinValue, double newMaxValue) {

    // Again, the minimum and maximum should not be equal
    if (newMinValue == newMaxValue) {
        throw invalid_argument("Axis minimum and maximum cannot be equal.");
    }

    // Store the new range
    minValue = newMinValue;
    maxValue = newMaxValue;
}


// This function changes where the axis will be drawn
// For example, I may want the axis to use positions 50 to 750
// instead of 0 to 500

void Axis::setScreenRange(
    double newScreenStart,
    double newScreenEnd
) {

    screenStart = newScreenStart;
    screenEnd = newScreenEnd;
}