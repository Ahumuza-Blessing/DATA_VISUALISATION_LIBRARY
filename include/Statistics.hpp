#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <vector>

using namespace std;

class Statistics
{
private:
    vector<double> data;

public:
    // Constructor
    explicit Statistics(vector<double> values);

    // Statistical calculations
    int calculateCount() const;
    double calculateMean() const;
    double calculateMedian() const;
    double calculateMinimum() const;
    double calculateMaximum() const;
    double calculateRange() const;
    double calculateStandardDeviation() const;

    // Returns all modes
    vector<double> calculateMode() const;
};

#endif // STATISTICS_HPP