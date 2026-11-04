#include "KDEPlot.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<double> data{1, 2, 2, 3, 4, 5};
    auto points = KDEPlot::estimate(data, 25);
    assert(points.size() == 25);
    for (const auto& point : points) {
        assert(std::isfinite(point.x));
        assert(std::isfinite(point.density));
        assert(point.density >= 0.0);
    }
    for (std::size_t i = 1; i < points.size(); ++i)
        assert(points[i].x > points[i - 1].x);

    auto custom = KDEPlot::estimate(data, 15, 0.5);
    assert(custom.size() == 15);
    assert(KDEPlot::estimate({3.0}, 10).size() == 10);

    bool rejectedEmpty = false;
    try { KDEPlot::estimate({}); }
    catch (const std::invalid_argument&) { rejectedEmpty = true; }
    assert(rejectedEmpty);

    bool rejectedCount = false;
    try { KDEPlot::estimate(data, 1); }
    catch (const std::invalid_argument&) { rejectedCount = true; }
    assert(rejectedCount);

    std::cout << "KDEPlot tests passed.\n";
}
