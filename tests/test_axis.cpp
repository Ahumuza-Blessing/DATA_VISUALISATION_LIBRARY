#include "Axis.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>

int main() {
    Axis axis(0, 100, 0, 500);
    assert(std::fabs(axis.scale(0) - 0) < 1e-9);
    assert(std::fabs(axis.scale(25) - 125) < 1e-9);
    assert(std::fabs(axis.scale(50) - 250) < 1e-9);
    assert(std::fabs(axis.scale(100) - 500) < 1e-9);
    auto ticks = axis.ticks(3);
    assert(ticks.size() == 3);
    assert(std::fabs(ticks[1] - 50) < 1e-9);
    axis.setRange(-10, 10);
    assert(std::fabs(axis.scale(0) - 250) < 1e-9);
    axis.setScreenRange(500, 0);
    assert(std::fabs(axis.scale(-10) - 500) < 1e-9);

    bool invalidRange = false;
    try { Axis bad(1, 1, 0, 100); }
    catch (const std::invalid_argument&) { invalidRange = true; }
    assert(invalidRange);

    bool invalidTicks = false;
    try { axis.ticks(1); }
    catch (const std::invalid_argument&) { invalidTicks = true; }
    assert(invalidTicks);

    std::cout << "Axis tests passed.\n";
}