#ifndef AXIS_HPP
#define AXIS_HPP

// Axis controls how values are placed on the graph

// The axis needs to calculate the scale used on the graph

// I will use the formula:
// Scale = (Highest Value - Lowest Value) / Number of divisions

// I need to receive the minimum and maximum values
// then use them when calculating the axis scale

// I also need to define how the values will later be positioned on the graph

class Axis {
private:
    // These store the actual data range
    double min_value;
    double max_value;

    // These store where the axis starts and ends on the screen
    double screen_start;
    double screen_end;

public:
    // I need a constructor to receive all the values needed by the axis
    Axis(
        double minValue,
        double maxValue,
        double screenStart,
        double screenEnd
    );

    // This will convert a real data value into a position on the graph
    double scale(double value) const;

    // These functions will allow me to access the stored values
    double getMin() const;
    double getMax() const;
    double getScreenStart() const;
    double getScreenEnd() const;

    // I may need to change the minimum and maximum values later
    void setRange(double newMinValue, double newMaxValue);

    // I may also need to change the screen drawing range
    void setScreenRange(double newScreenStart, double newScreenEnd);
};

#endif