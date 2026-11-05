#ifndef RENDERER_HPP // Prevents this header from being included more than once
#define RENDERER_HPP // Defines the header guard

#include "Annotation.hpp" // Provides annotations such as graph text and labels
#include "CountPlot.hpp"  // Provides category counts for count plots
#include "Histogram.hpp"  // Provides histogram bins
#include "KDEPlot.hpp"    // Provides KDE points for density plots

#include <string> // Provides std::string for SVG output and labels
#include <vector> // Provides std::vector for storing bins and points

// The Renderer turns the calculated plot values into SVG drawings.
// The different graphs should reuse Axis and Annotations where needed.
class Renderer {
public: // Functions accessible to other modules

    // The rest of the library will use this public interface.

    // Generates an SVG count plot from category frequencies.
    static std::string renderCountPlot(
        const CountPlot::Counts& counts, // Category names and their frequencies
        int width = 800,                 // SVG width, defaulting to 800
        int height = 500,                // SVG height, defaulting to 500
        const std::string& title = "Count Plot", // Graph title
        const Annotation& annotations = Annotation(), // Optional annotations
        const std::string& xLabel = "Category", // Horizontal axis label
        const std::string& yLabel = "Count" // Vertical axis label
    );

    // Generates an SVG histogram from previously calculated histogram bins.
    static std::string renderHistogram(
        const std::vector<HistogramBin>& bins, // Histogram intervals and counts
        int width = 800,                       // SVG width
        int height = 500,                      // SVG height
        const std::string& title = "Histogram", // Graph title
        const Annotation& annotations = Annotation(), // Optional annotations
        const std::string& xLabel = "Value",    // Horizontal axis label
        const std::string& yLabel = "Frequency" // Vertical axis label
    );

    // Generates an SVG density curve from KDE points.
    static std::string renderKDE(
        const std::vector<KDEPoint>& points, // Points containing x values and densities
        int width = 800,                    // SVG width
        int height = 500,                   // SVG height
        const std::string& title = "KDE Plot", // Graph title
        const Annotation& annotations = Annotation(), // Optional annotations
        const std::string& xLabel = "Value", // Horizontal axis label
        const std::string& yLabel = "Density" // Vertical axis label
    );

private: // Helper functions used internally by Renderer

    // Converts special text characters into XML-safe representations.
    static std::string escapeXML(const std::string& text);

    // Creates the opening SVG tag and background.
    static std::string svgStart(int width, int height);

    // Creates the closing SVG tag.
    static std::string svgEnd();
};

#endif // Ends the header guard
