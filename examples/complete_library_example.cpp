#include "Annotation.hpp"
#include "Axis.hpp"
#include "CountPlot.hpp"
#include "DataLoader.hpp"
#include "DataProcessor.hpp"
#include "Histogram.hpp"
#include "ImageExporter.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"
#include "Statistics.hpp"

#include <exception>
#include <iostream>
#include <string>

int main() {
    try {
        const auto rows = DataProcessor::cleanRows(
            DataLoader::loadCSV("data/input/student_marks.csv"));
        const auto marks = DataProcessor::toNumeric(
            DataProcessor::getColumn(rows, 2));
        const auto programmes = DataProcessor::getColumn(rows, 1);

        const double average = Statistics::mean(marks);
        const Axis marksAxis(
            Statistics::minimum(marks), Statistics::maximum(marks), 0, 500);
        std::cout << "Mean: " << average
                  << ", mapped position: " << marksAxis.scale(average) << "\n";

        const auto counts = CountPlot::calculate(programmes);
        const auto bins = Histogram::build(marks, 5);
        const auto density = KDEPlot::estimate(marks, 120);

        Annotation notes;
        notes.add(540, 80, "Mean mark: " + std::to_string(average));

        ImageExporter::saveSVG(
            Renderer::renderCountPlot(
                counts, 800, 500, "Student Programmes", notes,
                "Programme", "Students"),
            "complete_countplot.svg");
        ImageExporter::saveSVG(
            Renderer::renderHistogram(
                bins, 800, 500, "Student Marks", notes, "Mark", "Students"),
            "complete_histogram.svg");
        ImageExporter::saveSVG(
            Renderer::renderKDE(
                density, 800, 500, "Student Marks Density", notes,
                "Mark", "Density"),
            "complete_kdeplot.svg");

        std::cout << "Created three SVG graphs in "
                  << ImageExporter::outputFile("complete_histogram.svg")
                  << " (and the other two SVGs).\n";
    } catch (const std::exception& error) {
        std::cerr << "Full library example failed: " << error.what() << "\n";
        return 1;
    }
}
