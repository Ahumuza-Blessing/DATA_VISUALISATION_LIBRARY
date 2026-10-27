#include <iostream>
#include <vector>
#include <limits>
#include "data_Processor.hpp"

using namespace std;
using namespace data_Processor;

int main()
{
    // Sample data collected for visualization
    vector<double> rawData = {
        10, 20, 30,
        numeric_limits<double>::quiet_NaN(),
        40, 50
    };

    cout << "DATA PROCCESSOR MODULE EXAMPLE\n";

    // Step 1: Check whether data is empty
    if (isEmpty(rawData))
    {
        cout << "Error: No data available.\n";
        return 1;
    }

    cout << "Original data size: "
         << rawData.size() << "\n";

    // Step 2: Validate the original data
    cout << "Original data valid: "
         << (validateData(rawData) ? "Yes" : "No")
         << "\n";

    // Step 3: Remove invalid values
    vector<double> clean = cleanData(rawData);

    cout << "Cleaned data: ";
    for (double value : clean)
        cout << value << " ";

    cout << "\n";

    // Step 4: Normalize the cleaned data
    vector<double> normalized = normalizeData(clean);

    cout << "Normalized data: ";
    for (double value : normalized)
        cout << value << " ";

    cout << "\n";

    // Step 5: Calculate minimum and maximum
    cout << "Minimum value: "
         << findMinimum(clean) << "\n";

    cout << "Maximum value: "
         << findMaximum(clean) << "\n";

    cout << "Data processor completed successfully.\n";

    return 0;
}
