#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <string>

namespace DataProcessor {

    // Check whether the dataset is empty
    bool isEmpty(const std::vector<double>& data);

    // Check whether all values are valid numbers
    bool validateData(const std::vector<double>& data);

    // Remove invalid values from the dataset
    std::vector<double> cleanData(const std::vector<double>& data);

    // Normalize data to a range between 0 and 1
    std::vector<double> normalizeData(const std::vector<double>& data);

    // Calculate the minimum value
    double findMinimum(const std::vector<double>& data);

    // Calculate the maximum value
    double findMaximum(const std::vector<double>& data);

}

#endif