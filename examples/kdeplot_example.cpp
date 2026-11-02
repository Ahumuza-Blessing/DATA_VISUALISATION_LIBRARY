#include "KDEPlot.hpp"

#include <iostream>
#include <vector>

int main() {

    // Example data
    std::vector<double> marks{
        55, 60, 62, 65, 67,
        70, 70, 72, 75, 80,
        85, 90
    };

    // Generate 20 points for the KDE curve
    auto points = KDEPlot::estimate(marks, 20);

    std::cout << "KDE Plot Points\n";
    std::cout << "---------------\n";

    for (const auto& point : points) {
        std::cout
            << "x = " << point.x
            << ", density = " << point.density
            << "\n";
    }

    return 0;
}
