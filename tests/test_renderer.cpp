
#include "Annotation.hpp"
#include "CountPlot.hpp"
#include "Histogram.hpp"
#include "KDEPlot.hpp"
#include "Renderer.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    const CountPlot::Counts counts{{"A&B", 2}, {"C", 1}};
    const auto countSvg = Renderer::renderCountPlot(
        counts, 800, 500, "Count <Plot>", Annotation(), "Category &", "Count");
    assert(countSvg.find("<svg") != std::string::npos);
    assert(countSvg.find("Count &lt;Plot&gt;") != std::string::npos);
    assert(countSvg.find("A&amp;B") != std::string::npos);
    assert(countSvg.find("Category &amp;") != std::string::npos);

    const auto bins = Histogram::build({1.0, 2.0, 3.0, 4.0}, 2);
    const auto histogramSvg = Renderer::renderHistogram(
        bins, 800, 500, "Histogram", Annotation(), "Value", "Frequency");
    assert(histogramSvg.find("<rect") != std::string::npos);
    assert(histogramSvg.find("Frequency") != std::string::npos);

    const auto points = KDEPlot::estimate({1.0, 2.0, 3.0}, 10);
    const auto kdeSvg = Renderer::renderKDE(
        points, 800, 500, "Density", Annotation(), "Value", "Density");
    assert(kdeSvg.find("<polyline") != std::string::npos);
    assert(kdeSvg.find("Density") != std::string::npos);

    bool rejectedEmptyCount = false;
    try {
        Renderer::renderCountPlot({});
    } catch (const std::invalid_argument&) {
        rejectedEmptyCount = true;
    }
    assert(rejectedEmptyCount);

    bool rejectedInvalidSize = false;
    try {
        Renderer::renderKDE(points, 0, 500);
    } catch (const std::invalid_argument&) {
        rejectedInvalidSize = true;
    }
    assert(rejectedInvalidSize);

    std::cout << "Renderer tests passed.\n";
    return 0;
}
