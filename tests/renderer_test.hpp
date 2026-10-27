
#include "renderer.hpp"

#include <cassert>
#include <fstream>
#include <string>

int main() {
    dataviz::Plot plot;
    plot.title = "Renderer Test";
    plot.x_label = "X";
    plot.y_label = "Y";
    plot.points = {
        {1.0, 2.0},
        {2.0, 4.0},
        {3.0, 3.0}
    };

    dataviz::Renderer renderer;

    // Test that SVG generation returns content.
    std::string svg = renderer.render_svg(plot);
    assert(!svg.empty());
    assert(svg.find("<svg") != std::string::npos);
    assert(svg.find("Renderer Test") != std::string::npos);

    // Test saving the SVG file.
    const std::string filename = "renderer_test_output.svg";
    assert(renderer.save_svg(plot, filename));

    std::ifstream file(filename);
    assert(file.is_open());

    std::string saved_svg(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    assert(saved_svg.find("<svg") != std::string::npos);

    return 0;
}

