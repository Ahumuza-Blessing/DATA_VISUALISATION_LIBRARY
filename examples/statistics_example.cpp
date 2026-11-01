#include <iostream>
#include <vector>
#include "Statistics.hpp"

using namespace std;

int main()
{
    vector<double> data = {10, 20, 20, 30, 40};

    Statistics stats(data);

    cout << "STATISTICS EXAMPLE" << endl;
    

    cout << "Count: "
         << stats.calculateCount() << endl;

    cout << "Mean: "
         << stats.calculateMean() << endl;

    cout << "Median: "
         << stats.calculateMedian() << endl;

    cout << "Minimum: "
         << stats.calculateMinimum() << endl;

    cout << "Maximum: "
         << stats.calculateMaximum() << endl;

    cout << "Range: "
         << stats.calculateRange() << endl;

    cout << "Standard Deviation: "
         << stats.calculateStandardDeviation() << endl;

    vector<double> modes = stats.calculateMode();

    cout << "Mode: ";

    if (modes.empty())
    {
        cout << "No mode";
    }
    else
    {
        for (double mode : modes)
            cout << mode << " ";
    }

    cout << endl;

    return 0;
}