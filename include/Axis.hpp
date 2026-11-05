
#ifndef AXIS_HPP       // Checks whether AXIS_HPP has not already been defined
#define AXIS_HPP       // Defines the header guard to prevent repeated inclusion

#include <cstddef>     // Provides std::size_t for counting tick marks
#include <vector>      // Provides std::vector for storing multiple tick values

// The Axis class handles numerical scaling and tick generation.
class Axis {

private:                // These variables are hidden from outside code

    double minValue;    // Stores the minimum numerical value in the dataset
    double maxValue;    // Stores the maximum numerical value in the dataset

    double screenStart; // Stores the starting drawing coordinate
    double screenEnd;   // Stores the ending drawing coordinate

public:                 // These functions can be accessed from outside the class

    // Constructor: initializes the Axis object with four values.
    Axis(
        double minValue,     // Minimum numerical value
        double maxValue,     // Maximum numerical value
        double screenStart,  // Starting drawing coordinate
        double screenEnd     // Ending drawing coordinate
    );

    // Converts a numerical value into a screen coordinate.
    double scale(double value) const;

    // Generates evenly spaced tick values.
    // Defaults to six tick values when no count is supplied.
    std::vector<double> ticks(std::size_t count = 6) const;

    // Getter functions: return private values without modifying them.
    double getMin() const;          // Returns the minimum numerical value
    double getMax() const;          // Returns the maximum numerical value
    double getScreenStart() const;  // Returns the starting drawing coordinate
    double getScreenEnd() const;    // Returns the ending drawing coordinate

    // Setter functions: modify the numerical or drawing ranges.
    void setRange(double minValue, double maxValue); // Updates the data range
    void setScreenRange(double screenStart, double screenEnd); // Updates drawing coordinates
};

#endif // Ends the header guard
