#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>
#include "Statistics.hpp"

using namespace std;

bool approximatelyEqual(double a, double b, double tolerance = 0.001)
{
    return fabs(a - b) < tolerance;
}

int main()
{
    vector<double> data = {10, 20, 20, 30, 40};

    Statistics stats(data);

    // Testing count
    assert(stats.calculateCount() == 5);

    // Testing mean
    assert(approximatelyEqual(
        stats.calculateMean(), 24.0));

    // Testing median
    assert(approximatelyEqual(
        stats.calculateMedian(), 20.0));

    // Testing minimum
    assert(approximatelyEqual(
        stats.calculateMinimum(), 10.0));

    // Testing maximum
    assert(approximatelyEqual(
        stats.calculateMaximum(), 40.0));

    // Testing range
    assert(approximatelyEqual(
        stats.calculateRange(), 30.0));

    // Testing population standard deviation
    assert(approximatelyEqual(
        stats.calculateStandardDeviation(),
        sqrt(104.0)));

    // Testing mode
    vector<double> modes = stats.calculateMode();

    assert(modes.size() == 1);
    assert(approximatelyEqual(modes[0], 20.0));

    // Testing an empty dataset
    Statistics emptyStats(vector<double>{});

    assert(emptyStats.calculateCount() == 0);
    assert(approximatelyEqual(
        emptyStats.calculateMean(), 0.0));
    assert(approximatelyEqual(
        emptyStats.calculateMedian(), 0.0));

    cout << "All statistics tests passed successfully!"
         << endl;

    return 0;
}