
#include "DataProcessing.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace DataProcessing {

    bool isEmpty(const std::vector<double>& data) {
        return data.empty();
    }

    bool validateData(const std::vector<double>& data) {
        if (data.empty()) {
            return false;
        }

        for (double value : data) {
            if (!std::isfinite(value)) {
                return false;
            }
        }

        return true;
    }

    std::vector<double> cleanData(
        const std::vector<double>& data) {

        std::vector<double> cleanedData;

        for (double value : data) {
            if (std::isfinite(value)) {
                cleanedData.push_back(value);
            }
        }

        return cleanedData;
    }

    std::vector<double> normalizeData(
        const std::vector<double>& data) {

        std::vector<double> cleanedData = cleanData(data);

        if (cleanedData.empty()) {
            return {};
        }

        double minValue = findMinimum(cleanedData);
        double maxValue = findMaximum(cleanedData);

        if (minValue == maxValue) {
            return std::vector<double>(
                cleanedData.size(), 0.0);
        }

        std::vector<double> normalizedData;

        for (double value : cleanedData) {
            normalizedData.push_back(
                (value - minValue) / (maxValue - minValue));
        }

        return normalizedData;
    }

    double findMinimum(const std::vector<double>& data) {
        if (!validateData(data)) {
            throw std::invalid_argument(
                "Cannot find minimum of invalid data.");
        }

        return *std::min_element(data.begin(), data.end());
    }

    double findMaximum(const std::vector<double>& data) {
        if (!validateData(data)) {
            throw std::invalid_argument(
                "Cannot find maximum of invalid data.");
        }

        return *std::max_element(data.begin(), data.end());
    }

}
