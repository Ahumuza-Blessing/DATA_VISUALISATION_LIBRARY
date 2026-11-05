#include "Annotation.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "ImageExporter.hpp"
#include "Renderer.hpp"
#include "Statistics.hpp"

#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

std::string formatStatistic(double value) {
    std::ostringstream formatted;
    formatted << std::fixed << std::setprecision(4) << value;

    std::string result = formatted.str();
    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
    if (!result.empty() && result.back() == '.') {
        result.pop_back();
    }
    return result;
}

} // namespace

int main() {
    try {
        // First read the marks from our sample CSV and turn them into numbers.
        auto rows = DataProcessor::cleanRows(
            DataLoader::loadCSV("data/input/student_marks.csv"));
        auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(rows, 2));

        const auto modes = Statistics::mode(marks);
        const double firstQuartile = Statistics::firstQuartile(marks);
        const double thirdQuartile = Statistics::thirdQuartile(marks);
        const double variance = Statistics::variance(marks);
        const double standardDeviation = Statistics::standardDeviation(marks);

        std::cout << "Mode(s): ";
        if (modes.empty()) {
            std::cout << "none";
        } else {
            for (std::size_t i = 0; i < modes.size(); ++i) {
                if (i > 0) {
                    std::cout << ", ";
                }
                std::cout << formatStatistic(modes[i]);
            }
        }
        std::cout << "\nMean: " << formatStatistic(Statistics::mean(marks))
                  << "\nFirst quartile (Q1): " << formatStatistic(firstQuartile)
                  << "\nThird quartile (Q3): " << formatStatistic(thirdQuartile)
                  << "\nInterquartile range (IQR): "
                  << formatStatistic(Statistics::interquartileRange(marks))
                  << "\nPopulation variance: " << formatStatistic(variance)
                  << "\nStandard deviation: "
                  << formatStatistic(standardDeviation) << "\n";

        // The histogram module groups the marks; the Renderer does the drawing.
        auto bins = Histogram::build(marks, 5);
        Annotation notes;
        std::string modeLabel = "Mode(s): ";
        if (modes.empty()) {
            modeLabel += "none";
        } else {
            for (std::size_t i = 0; i < modes.size(); ++i) {
                if (i > 0) {
                    modeLabel += ", ";
                }
                modeLabel += formatStatistic(modes[i]);
            }
        }

        notes.add(520, 78, "Mean mark: " + formatStatistic(Statistics::mean(marks)));
        notes.add(520, 96, modeLabel);
        notes.add(520, 114, "Q1: " + formatStatistic(firstQuartile));
        notes.add(520, 132, "Q3: " + formatStatistic(thirdQuartile));
        notes.add(520, 150, "IQR: " + formatStatistic(
            Statistics::interquartileRange(marks)));
        notes.add(520, 168, "Variance: " + formatStatistic(variance));
        notes.add(520, 186, "Std. deviation: " + formatStatistic(standardDeviation));

        std::string svg = Renderer::renderHistogram(
            bins, 800, 500, "Student Marks Histogram", notes, "Mark", "Frequency");
        ImageExporter::saveSVG(svg, "histogram_example.svg");

        std::cout << "Created " << ImageExporter::outputFile("histogram_example.svg") << " with "
                  << bins.size() << " bins.\n";
    } catch (const std::exception& error) {
        std::cerr << "Histogram example failed: " << error.what() << "\n";
        return 1;
    }
}