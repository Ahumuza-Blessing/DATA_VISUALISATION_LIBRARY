
#include "Renderer.hpp"
#include "CountPlot.hpp"
#include "Histogram.hpp"
#include "KDEPlot.hpp"
#include "Annotation.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>
int main() {
    Annotation note;
    note.add(100, 100, "Peak & high");
    auto svg1 = Renderer::renderCountPlot(CountPlot::calculate({"A", "B", "A"}), 500, 350, "Test", note);
    assert(svg1.find("<svg") != std::string::npos);
    assert(svg1.find("Peak &amp; high") != std::string::npos);
    auto svg2 = Renderer::renderHistogram(Histogram::build({1, 2, 3}, 2), 500, 350);
    assert(svg2.find("<rect") != std::string::npos);
    auto svg3 = Renderer::renderKDE(KDEPlot::estimate({1, 2, 3}, 20), 500, 350);
    assert(svg3.find("<polyline") != std::string::npos);
    bool threw = false;
    try { Renderer::renderCountPlot({}); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    std::cout << "Renderer tests passed.\n";
}
