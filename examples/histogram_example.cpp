#include "Annotation.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "ImageExporter.hpp"
#include "Renderer.hpp"
#include "Statistics.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        // First read the marks from our sample CSV and turn them into numbers.
        auto rows = DataProcessor::cleanRows(DataLoader::loadCSV("data/input/sample.csv"));
        auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(rows, 2));

        // The histogram module groups the marks; the Renderer does the drawing.
        auto bins = Histogram::build(marks, 5);
        Annotation notes;
        notes.add(520, 78, "Mean mark: " + std::to_string(Statistics::mean(marks)));

        std::string svg = Renderer::renderHistogram(
            bins, 800, 500, "Student Marks Histogram", notes);
        ImageExporter::saveSVG(svg, "histogram_example.svg");

        std::cout << "Created " << ImageExporter::outputFile("histogram_example.svg") << " with "
                  << bins.size() << " bins.\n";
    } catch (const std::exception& error) {
        std::cerr << "Histogram example failed: " << error.what() << "\n";
        return 1;
    }
}