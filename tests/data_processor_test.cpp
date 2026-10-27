
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include "data_Processor.hpp"

using namespace std;
using namespace data_Processor;

int main()
{
    // Test 1: Check whether data is empty
    vector<double> emptyData;
    cout << "TEST 1: Empty Data\n";
    cout << "Is empty: "
         << (isEmpty(emptyData) ? "PASS" : "FAIL") << "\n\n";

    // Test 2: Validate data
    vector<double> data = {10, 20, 30, 40, 50};

    cout << "TEST 2: Validate Data\n";
    cout << "Valid data: "
         << (validateData(data) ? "PASS" : "FAIL") << "\n\n";

    // Test 3: Clean invalid data
    vector<double> dirtyData = {
        10, 20,
        numeric_limits<double>::quiet_NaN(),
        30,
        numeric_limits<double>::infinity(),
        40
    };

    vector<double> cleanedData = cleanData(dirtyData);

    cout << "TEST 3: Clean Data\n";
    cout << "Cleaned data: ";

    for (double value : cleanedData)
        cout << value << " ";

    cout << "\nCleaning successful: "
         << (cleanedData.size() == 4 ? "PASS" : "FAIL")
         << "\n\n";

    // Test 4: Normalize data
    vector<double> normalizedData = normalizeData(data);

    cout << "TEST 4: Normalize Data\n";
    cout << "Normalized values: ";

    for (double value : normalizedData)
        cout << value << " ";

    bool normalizationPassed =
        normalizedData.size() == 5 &&
        normalizedData.front() == 0.0 &&
        normalizedData.back() == 1.0;

    cout << "\nNormalization: "
         << (normalizationPassed ? "PASS" : "FAIL")
         << "\n\n";

    // Test 5: Find minimum
    cout << "TEST 5: Find Minimum\n";
    double minimum = findMinimum(data);

    cout << "Minimum value: " << minimum << "\n";
    cout << "Test result: "
         << (minimum == 10 ? "PASS" : "FAIL") << "\n\n";

    // Test 6: Find maximum
    cout << "TEST 6: Find Maximum\n";
    double maximum = findMaximum(data);

    cout << "Maximum value: " << maximum << "\n";
    cout << "Test result: "
         << (maximum == 50 ? "PASS" : "FAIL") << "\n\n";

    // Test 7: Check error handling for empty data
    cout << "TEST 7: Empty Data Error Handling\n";

    try
    {
        findMinimum(emptyData);
        cout << "FAIL: Expected an exception\n";
    }
    catch (const invalid_argument&)
    {
        cout << "PASS: Empty data handled correctly\n";
    }

    cout << "\nAll tests completed.\n";

    return 0;
}
