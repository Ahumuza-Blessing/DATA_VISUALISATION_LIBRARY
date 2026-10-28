#include "Statistics.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

Statistics::Statistics(vector<double> values)
    : data(values)
{
}

int Statistics::calculateCount() const
{
    return static_cast<int>(data.size());
}

double Statistics::calculateMean() const
{
    if (data.empty())
        return 0.0;

    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double Statistics::calculateMedian() const
{
    if (data.empty())
        return 0.0;

    vector<double> sorted = data;
    sort(sorted.begin(), sorted.end());

    size_t n = sorted.size();

    if (n % 2 == 1)
        return sorted[n / 2];

    return (sorted[n / 2 - 1] + sorted[n / 2]) / 2.0;
}

double Statistics::calculateMinimum() const
{
    if (data.empty())
        return 0.0;

    return *min_element(data.begin(), data.end());
}

double Statistics::calculateMaximum() const
{
    if (data.empty())
        return 0.0;

    return *max_element(data.begin(), data.end());
}

double Statistics::calculateRange() const
{
    if (data.empty())
        return 0.0;

    return calculateMaximum() - calculateMinimum();
}

double Statistics::calculateStandardDeviation() const
{
    if (data.empty())
        return 0.0;

    double mean = calculateMean();
    double sumSquares = 0.0;

    for (double value : data)
    {
        double difference = value - mean;
        sumSquares += difference * difference;
    }

    // Population standard deviation
    double variance = sumSquares / data.size();

    return sqrt(variance);
}

vector<double> Statistics::calculateMode() const
{
    map<double, int> frequencies;
    vector<double> modes;

    for (double value : data)
        frequencies[value]++;

    int highestFrequency = 0;

    for (const auto& item : frequencies)
    {
        if (item.second > highestFrequency)
            highestFrequency = item.second;
    }

    // No mode when every value occurs only once
    if (highestFrequency <= 1)
        return modes;

    for (const auto& item : frequencies)
    {
        if (item.second == highestFrequency)
            modes.push_back(item.first);
    }

    return modes;
}