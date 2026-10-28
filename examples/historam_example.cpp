#include "histogram.hpp"
#include "renderer.hpp"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main()
{
    // Exam marks for a class
    std::vector<double> marks{
        45, 52, 55, 58, 60, 61, 62, 64, 65, 67,
        68, 70, 70, 71, 72, 74, 75, 75, 78, 80,
        82, 85, 88, 90, 95
    };

    const std::size_t bins = 6;

    try
    {
        dataviz::Histogram histogram(marks, bins);

        std::cout << "HISTOGRAM EXAMPLE\n";
        std::cout << "Values: " << histogram.totalCount() << "\n";
        std::cout << "Range:  " << histogram.rangeMin()
                  << " to " << histogram.rangeMax() << "\n";
        std::cout << "Bins:   " << histogram.numBins()
                  << " (width " << histogram.binWidth() << ")\n\n";

        const auto& counts = histogram.counts();
        const auto& edges = histogram.binEdges();

        std::cout << std::fixed << std::setprecision(1);

        // Text bar chart
        for (std::size_t i = 0; i < counts.size(); ++i)
        {
            std::cout << "[" << std::setw(5) << edges[i] << ", "
                      << std::setw(5) << edges[i + 1]
                      << (i + 1 == counts.size() ? "]" : ")")
                      << " | " << std::string(counts[i], '#')
                      << " " << counts[i] << "\n";
        }

        // Export an SVG: bin centre on x, count on y
        dataviz::Plot plot;
        plot.title = "Exam Marks Histogram";
        plot.x_label = "Mark (bin centre)";
        plot.y_label = "Count";

        for (std::size_t i = 0; i < counts.size(); ++i)
        {
            double centre = (edges[i] + edges[i + 1]) / 2.0;
            plot.points.push_back({centre, static_cast<double>(counts[i])});
        }

        dataviz::Renderer renderer;

        if (renderer.save_svg(plot, "histogram_example.svg"))
        {
            std::cout << "\nSaved histogram_example.svg\n";
        }
        else
        {
            std::cerr << "\nCould not save SVG.\n";
            return 1;
        }
    }
    catch (const std::invalid_argument& error)
    {
        std::cerr << "Error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}