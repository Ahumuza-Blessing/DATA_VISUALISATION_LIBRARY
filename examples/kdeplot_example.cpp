#include "Annotation.hpp"
#include "ImageExporter.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

int main() {
    try {
        const std::vector<double> marks{
            55, 60, 62, 65, 67,
            70, 70, 72, 75, 80,
            85, 90
        };
        const auto points = KDEPlot::estimate(marks, 100);
        const auto svg = Renderer::renderKDE(
            points, 800, 500, "Student Marks KDE", Annotation(), "Mark", "Density");
        ImageExporter::saveSVG(svg, "kdeplot_example.svg");

        std::cout << "Created "
                  << ImageExporter::outputFile("kdeplot_example.svg")
                  << " with " << points.size() << " KDE points.\n";
    } catch (const std::exception& error) {
        std::cerr << "KDE example failed: " << error.what() << "\n";
        return 1;
    }
    return 0;
}
