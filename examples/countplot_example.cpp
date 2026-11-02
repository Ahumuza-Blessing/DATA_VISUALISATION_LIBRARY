#include "Annotation.hpp"
#include "CountPlot.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "ImageExporter.hpp"
#include "Renderer.hpp"

#include <exception>
#include <iostream>
#include <string>

int main() {
    try {
        // A count plot uses the programme names rather than numerical marks.
        auto rows = DataProcessor::cleanRows(DataLoader::loadCSV("data/input/sample.csv"));
        auto programmes = DataProcessor::getColumn(rows, 1);
        auto counts = CountPlot::calculate(programmes);

        Annotation notes;
        notes.add(560, 80, "Programmes: " + std::to_string(counts.size()));

        auto svg = Renderer::renderCountPlot(
            counts, 800, 500, "Students by Programme", notes);
        ImageExporter::saveSVG(svg, "countplot_example.svg");

        std::cout << "Created " << ImageExporter::outputFile("countplot_example.svg") << " for "
                  << counts.size() << " programme categories.\n";
    } catch (const std::exception& error) {
        std::cerr << "Count plot example failed: " << error.what() << "\n";
        return 1;
    }
}
