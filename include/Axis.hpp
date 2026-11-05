
#ifndef AXIS_HPP
#define AXIS_HPP

#include <cstddef>     // Provides std::size_t for counting tick marks
#include <vector>      // Provides std::vector for storing tick values
#include <type_traits> // Provides tools for checking data types at compile time

// The Axis class handles numerical scaling and tick generation.
class Axis {

private: // These variables are hidden from outside code

    double minValue;    // Stores the minimum numerical value
    double maxValue;    // Stores the maximum numerical value

    double screenStart; // Stores the starting drawing coordinate
    double screenEnd;   // Stores the ending drawing coordinate

public: // These functions can be accessed from outside the class

    // Constructor: initializes the Axis object with four values.
    Axis(
        double minValue,
        double maxValue,
        double screenStart,
        double screenEnd
    );

    // Converts a numerical value into a screen coordinate.
    // This is the original scaling function.
    double scale(double value) const;

    // TEMPLATE FUNCTION
    // template <typename T> allows the function to accept
    // different numerical data types, such as int and float.
    //
    // T represents the data type supplied by the caller.
    // The compiler determines T when the function is called.
    template <typename T>
    double scale(T value) const {

        // Checks at compile time that T is a numerical type.
        // std::is_arithmetic_v<T> accepts standard integer
        // and floating-point types.
        static_assert(
            std::is_arithmetic_v<T>,
            "Axis requires a numeric data type."
        );

        // Converts the supplied value into a double.
        // Calls the original scale(double) function.
        // This avoids repeating the scaling formula.
        return scale(static_cast<double>(value));
    }

    // Generates evenly spaced tick values.
    // Defaults to six tick values.
    std::vector<double> ticks(std::size_t count = 6) const;

    // Getter functions: return private values.
    double getMin() const;
    double getMax() const;
    double getScreenStart() const;
    double getScreenEnd() const;

    // Setter functions: update the axis ranges.
    void setRange(double minValue, double maxValue);
    void setScreenRange(double screenStart, double screenEnd);
};

#endif
