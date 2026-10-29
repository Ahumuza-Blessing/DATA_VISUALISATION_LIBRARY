#include "KDEPlot.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {

    // Test 1: KDE should return the requested number of points
    {
        std::vector<double> values{1, 2, 2, 3, 4, 5};

        auto points = KDEPlot::estimate(values, 25);

        assert(points.size() == 25);
    }

    // Test 2: Density values should never be negative
    {
        std::vector<double> values{10, 20, 30, 40, 50};

        auto points = KDEPlot::estimate(values, 30);

        for (const auto& point : points) {
            assert(point.density >= 0.0);
        }
    }

    // Test 3: X values should increase from left to right
    {
        std::vector<double> values{1, 2, 3, 4, 5};

        auto points = KDEPlot::estimate(values, 20);

        for (std::size_t i = 1; i < points.size(); ++i) {
            assert(points[i].x > points[i - 1].x);
        }
    }

    // Test 4: KDE should work with a custom bandwidth
    {
        std::vector<double> values{1, 2, 3, 4, 5};

        auto points = KDEPlot::estimate(values, 15, 0.5);

        assert(points.size() == 15);

        for (const auto& point : points) {
            assert(point.density >= 0.0);
        }
    }

    // Test 5: Empty data should produce an error
    {
        std::vector<double> emptyData;

        bool errorCaught = false;

        try {
            KDEPlot::estimate(emptyData);
        }
        catch (const std::invalid_argument&) {
            errorCaught = true;
        }

        assert(errorCaught);
    }

    // Test 6: Point count below 2 should produce an error
    {
        std::vector<double> values{1, 2, 3};

        bool errorCaught = false;

        try {
            KDEPlot::estimate(values, 1);
        }
        catch (const std::invalid_argument&) {
            errorCaught = true;
        }

        assert(errorCaught);
    }

    std::cout << "All KDEPlot tests passed.\n";

    return 0;
}
