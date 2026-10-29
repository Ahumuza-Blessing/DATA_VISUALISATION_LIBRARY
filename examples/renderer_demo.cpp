

#include "renderer.hpp"

#include <iostream>
#include <string>

int main() {
    dataviz::Plot plot;

    plot.title = "Week 3 Renderer Test";
    plot.x_label = "X Values";
    plot.y_label = "Y Values";

    plot.points = {
        {1.0, 2.0},
        {2.0, 4.0},
        {3.0, 3.0},
        {4.0, 5.0}
    };

    dataviz::Renderer renderer;

    std::string svg = renderer.render_svg(plot);

    if (svg.empty()) {
        std::cerr << "Test failed: SVG is empty.\n";
        return 1;
    }

    std::cout << "SVG generated successfully.\n";

    if (renderer.save_svg(plot, "week3_renderer_test.svg")) {
        std::cout << "Test passed: SVG saved successfully.\n";
    } else {
        std::cerr << "Test failed: Could not save SVG.\n";
        return 1;
    }

    return 0;
}
