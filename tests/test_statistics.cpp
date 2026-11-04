
#include "Statistics.hpp"

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

// Compare floating-point numbers safely.
bool approximatelyEqual(
    double actual,
    double expected,
    double tolerance = 1e-9
) {
    return std::fabs(actual - expected) < tolerance;
}

// Verify that an operation rejects invalid input.
template <typename Function>
void expectInvalidArgument(Function function) {
    bool caught = false;

    try {
        function();
    } catch (const std::invalid_argument&) {
        caught = true;
    }

    assert(caught);
}

int main() {

    // ============================================
    // 1. COUNT
    // ============================================

    std::vector<double> data{1, 2, 3, 4, 5};

    assert(Statistics::count(data) == 5);
    assert(Statistics::count({}) == 0);
    assert(Statistics::count({10}) == 1);

    // ============================================
    // 2. MEAN
    // ============================================

    assert(approximatelyEqual(
        Statistics::mean(data), 3.0
    ));

    assert(approximatelyEqual(
        Statistics::mean({10, 20, 30, 40}), 25.0
    ));

    assert(approximatelyEqual(
        Statistics::mean({-10, 0, 10}), 0.0
    ));

    assert(approximatelyEqual(
        Statistics::mean({5}), 5.0
    ));

    // ============================================
    // 3. MINIMUM AND MAXIMUM
    // ============================================

    assert(approximatelyEqual(
        Statistics::minimum(data), 1.0
    ));

    assert(approximatelyEqual(
        Statistics::maximum(data), 5.0
    ));

    assert(approximatelyEqual(
        Statistics::minimum({-8, 2, 4, -3}), -8.0
    ));

    assert(approximatelyEqual(
        Statistics::maximum({-8, 2, 4, -3}), 4.0
    ));

    // ============================================
    // 4. MEDIAN
    // ============================================

    // Odd number of values
    assert(approximatelyEqual(
        Statistics::median({1, 2, 3, 4, 5}), 3.0
    ));

    // Even number of values
    assert(approximatelyEqual(
        Statistics::median({1, 2, 3, 4}), 2.5
    ));

    // Unsorted values
    assert(approximatelyEqual(
        Statistics::median({9, 1, 5, 3, 7}), 5.0
    ));

    // Repeated values
    assert(approximatelyEqual(
        Statistics::median({2, 2, 4, 6}), 3.0
    ));

    // Single value
    assert(approximatelyEqual(
        Statistics::median({7}), 7.0
    ));

    // ============================================
    // 5. VARIANCE (POPULATION)
    // ============================================

    // Population variance: divide by N.
    assert(approximatelyEqual(
        Statistics::variance({1, 2, 3, 4, 5}), 2.0
    ));

    assert(approximatelyEqual(
        Statistics::variance({2, 4, 6, 8}), 5.0
    ));

    assert(approximatelyEqual(
        Statistics::variance({5, 5, 5, 5}), 0.0
    ));

    assert(approximatelyEqual(
        Statistics::variance({10}), 0.0
    ));

    // ============================================
    // 6. STANDARD DEVIATION
    // ============================================

    assert(approximatelyEqual(
        Statistics::standardDeviation(data),
        std::sqrt(2.0)
    ));

    assert(approximatelyEqual(
        Statistics::standardDeviation({2, 4, 6, 8}),
        std::sqrt(5.0)
    ));

    assert(approximatelyEqual(
        Statistics::standardDeviation({5, 5, 5, 5}),
        0.0
    ));

    // ============================================
    // 7. MODE
    // ============================================

    // One mode
    auto singleMode = Statistics::mode({
        1, 2, 2, 2, 3, 4, 5
    });

    assert(singleMode.size() == 1);
    assert(approximatelyEqual(singleMode[0], 2.0));

    // Two modes
    auto twoModes = Statistics::mode({
        1, 2, 2, 3, 3, 4
    });

    assert(twoModes.size() == 2);
    assert(approximatelyEqual(twoModes[0], 2.0));
    assert(approximatelyEqual(twoModes[1], 3.0));

    // Three modes
    auto threeModes = Statistics::mode({
        1, 1, 2, 2, 3, 3, 4
    });

    assert(threeModes.size() == 3);
    assert(approximatelyEqual(threeModes[0], 1.0));
    assert(approximatelyEqual(threeModes[1], 2.0));
    assert(approximatelyEqual(threeModes[2], 3.0));

    // No repeated values: no mode
    assert(
        Statistics::mode({1, 2, 3, 4, 5}).empty()
    );

    // Negative values
    auto negativeMode = Statistics::mode({
        -3, -3, -1, 0, 2
    });

    assert(negativeMode.size() == 1);
    assert(approximatelyEqual(negativeMode[0], -3.0));

    // One observation has no mode under our convention.
    assert(Statistics::mode({5}).empty());

    // ============================================
    // 8. FIRST QUARTILE (Q1)
    // ============================================

    // Even number of observations
    assert(approximatelyEqual(
        Statistics::firstQuartile({
            1, 2, 3, 4, 5, 6, 7, 8
        }),
        2.5
    ));

    // Odd number of observations:
    // Exclude the overall median.
    assert(approximatelyEqual(
        Statistics::firstQuartile({
            1, 2, 3, 4, 5, 6, 7
        }),
        2.0
    ));

    // Unsorted values
    assert(approximatelyEqual(
        Statistics::firstQuartile({
            8, 3, 1, 7, 2, 6, 4, 5
        }),
        2.5
    ));

    // Single value
    assert(approximatelyEqual(
        Statistics::firstQuartile({10}),
        10.0
    ));

    // ============================================
    // 9. THIRD QUARTILE (Q3)
    // ============================================

    assert(approximatelyEqual(
        Statistics::thirdQuartile({
            1, 2, 3, 4, 5, 6, 7, 8
        }),
        6.5
    ));

    assert(approximatelyEqual(
        Statistics::thirdQuartile({
            1, 2, 3, 4, 5, 6, 7
        }),
        6.0
    ));

    assert(approximatelyEqual(
        Statistics::thirdQuartile({
            8, 3, 1, 7, 2, 6, 4, 5
        }),
        6.5
    ));

    assert(approximatelyEqual(
        Statistics::thirdQuartile({10}),
        10.0
    ));

    // ============================================
    // 10. INTERQUARTILE RANGE (IQR)
    // ============================================

    assert(approximatelyEqual(
        Statistics::interquartileRange({
            1, 2, 3, 4, 5, 6, 7, 8
        }),
        4.0
    ));

    assert(approximatelyEqual(
        Statistics::interquartileRange({
            1, 2, 3, 4, 5, 6, 7
        }),
        4.0
    ));

    // All equal values
    assert(approximatelyEqual(
        Statistics::interquartileRange({
            5, 5, 5, 5, 5
        }),
        0.0
    ));

    // Single value
    assert(approximatelyEqual(
        Statistics::interquartileRange({10}),
        0.0
    ));

    // ============================================
    // 11. INVALID AND EMPTY DATA
    // ============================================

    expectInvalidArgument([] {
        Statistics::mean({});
    });

    expectInvalidArgument([] {
        Statistics::minimum({});
    });

    expectInvalidArgument([] {
        Statistics::maximum({});
    });

    expectInvalidArgument([] {
        Statistics::median({});
    });

    expectInvalidArgument([] {
        Statistics::variance({});
    });

    expectInvalidArgument([] {
        Statistics::standardDeviation({});
    });

    expectInvalidArgument([] {
        Statistics::mode({});
    });

    expectInvalidArgument([] {
        Statistics::firstQuartile({});
    });

    expectInvalidArgument([] {
        Statistics::thirdQuartile({});
    });

    expectInvalidArgument([] {
        Statistics::interquartileRange({});
    });

    // ============================================
    // 12. NaN AND INFINITY VALIDATION
    // ============================================

    const double nan =
        std::numeric_limits<double>::quiet_NaN();

    const double infinity =
        std::numeric_limits<double>::infinity();

    expectInvalidArgument([&] {
        Statistics::mean({1, nan, 3});
    });

    expectInvalidArgument([&] {
        Statistics::median({1, infinity, 3});
    });

    expectInvalidArgument([&] {
        Statistics::variance({1, nan});
    });

    expectInvalidArgument([&] {
        Statistics::standardDeviation({1, infinity});
    });

    expectInvalidArgument([&] {
        Statistics::mode({1, nan, 2});
    });

    expectInvalidArgument([&] {
        Statistics::firstQuartile({1, infinity, 3});
    });

    expectInvalidArgument([&] {
        Statistics::thirdQuartile({1, nan, 3});
    });

    expectInvalidArgument([&] {
        Statistics::interquartileRange({1, infinity, 3});
    });

    // ============================================
    // ALL TESTS PASSED
    // ============================================

    std::cout
        << "All Statistics tests passed successfully.\n";

    return 0;
}
