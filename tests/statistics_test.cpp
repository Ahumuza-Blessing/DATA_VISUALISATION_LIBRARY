#include "Statistics.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    std::vector<double> data{1, 2, 3, 4, 5};
    assert(Statistics::count(data) == 5);
    assert(std::fabs(Statistics::mean(data) - 3.0) < 1e-9);
    assert(std::fabs(Statistics::median(data) - 3.0) < 1e-9);
    assert(std::fabs(Statistics::minimum(data) - 1.0) < 1e-9);
    assert(std::fabs(Statistics::maximum(data) - 5.0) < 1e-9);
    assert(std::fabs(Statistics::variance(data) - 2.0) < 1e-9);
    assert(std::fabs(Statistics::standardDeviation(data) - std::sqrt(2.0)) < 1e-9);
    assert(std::fabs(Statistics::median({1, 2, 3, 4}) - 2.5) < 1e-9);

    bool errorCaught = false;
    try { Statistics::mean({}); }
    catch (const std::invalid_argument&) { errorCaught = true; }
    assert(errorCaught);

    std::cout << "Statistics tests passed.\n";
}