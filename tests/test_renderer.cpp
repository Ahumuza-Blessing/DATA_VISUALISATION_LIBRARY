
#include "Annotation.hpp" // Provides the Annotation class for graph text
#include "CountPlot.hpp"  // Provides the category-count data type
#include "Histogram.hpp"  // Provides the Histogram class and bin calculations
#include "KDEPlot.hpp"    // Provides KDE calculations and point data
#include "Renderer.hpp"   // Provides the Renderer functions being tested

#include <cassert>   // Provides assert() for verifying test conditions
#include <iostream>  // Provides std::cout for displaying test results
#include <stdexcept> // Provides std::invalid_argument for exception tests
#include <string>    // Provides std::string and string-search functions
#include <vector>    // Provides std::vector for storing numerical data

int main() { // Entry point of the Renderer test program

    // Creates a map containing two categories and their frequencies.
    // The first category contains an ampersand to test XML escaping.
    const CountPlot::Counts counts{{"A&B", 2}, {"C", 1}};

    // Generates an SVG count plot using the category counts.
    // The title and x-axis label contain special XML characters.
    const auto countSvg = Renderer::renderCountPlot(
        counts, 800, 500, "Count <Plot>", Annotation(), "Category &", "Count");

    // Checks that the generated SVG contains an opening SVG tag.
    // find() searches for text inside a string.
    // std::string::npos means the searched text was not found.
    assert(countSvg.find("<svg") != std::string::npos);

    // Verifies that the title's < and > characters were escaped.
    // This helps prevent the title from being interpreted as XML markup.
    assert(countSvg.find("Count &lt;Plot&gt;") != std::string::npos);

    // Verifies that the ampersand in category A&B was escaped.
    assert(countSvg.find("A&amp;B") != std::string::npos);

    // Verifies that the ampersand in the horizontal axis label was escaped.
    assert(countSvg.find("Category &amp;") != std::string::npos);

    // Creates two histogram bins from four numerical values.
    // Histogram::build() prepares the data for the Renderer.
    const auto bins = Histogram::build({1.0, 2.0, 3.0, 4.0}, 2);

    // Generates an SVG histogram from the calculated bins.
    const auto histogramSvg = Renderer::renderHistogram(
        bins, 800, 500, "Histogram", Annotation(), "Value", "Frequency");

    // Checks that the histogram SVG contains a rectangle element.
    // Rectangles are used to represent histogram bars.
    assert(histogramSvg.find("<rect") != std::string::npos);

    // Checks that the SVG contains the expected vertical axis label.
    assert(histogramSvg.find("Frequency") != std::string::npos);

    // Estimates KDE density values from three numerical observations.
    // The second argument requests 10 evaluation points.
    const auto points = KDEPlot::estimate({1.0, 2.0, 3.0}, 10);

    // Generates an SVG KDE plot from the estimated density points.
    const auto kdeSvg = Renderer::renderKDE(
        points, 800, 500, "Density", Annotation(), "Value", "Density");

    // Verifies that the SVG contains a polyline element.
    // The Renderer uses a polyline to connect KDE points.
    assert(kdeSvg.find("<polyline") != std::string::npos);

    // Verifies that the expected text appears in the SVG.
    assert(kdeSvg.find("Density") != std::string::npos);

    // Creates a boolean flag to record whether an empty count plot is rejected.
    bool rejectedEmptyCount = false;

    try { // Attempts an operation expected to throw an exception

        // Passes an empty category map to the Renderer.
        // The Renderer should reject an empty count plot.
        Renderer::renderCountPlot({});

    } catch (const std::invalid_argument&) {
        // Executes when the expected invalid_argument exception is caught.
        rejectedEmptyCount = true;
    }

    // Verifies that the Renderer rejected the empty count plot.
    assert(rejectedEmptyCount);

    // Creates a flag to check whether invalid SVG dimensions are rejected.
    bool rejectedInvalidSize = false;

    try { // Attempts to render a KDE graph with an invalid width

        // Width 0 is invalid because SVG dimensions must be positive.
        Renderer::renderKDE(points, 0, 500);

    } catch (const std::invalid_argument&) {
        // Records that the expected exception occurred.
        rejectedInvalidSize = true;
    }

    // Verifies that the Renderer rejected the invalid dimensions.
    assert(rejectedInvalidSize);

    // Displays a success message if all enabled assertions pass.
    std::cout << "Renderer tests passed.\n";

    return 0; // Ends the test program successfully
}
