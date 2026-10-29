

#include "renderer.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

namespace dataviz {

std::string Renderer::render_svg(const Plot& plot) const {
    const int width = 800;
    const int height = 600;
    const int margin = 80;

    std::ostringstream svg;

    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << width << "\" "
        << "height=\"" << height << "\" "
        << "viewBox=\"0 0 " << width << " " << height << "\">\n";

    // Background
    svg << "<rect width=\"100%\" height=\"100%\" "
        << "fill=\"white\"/>\n";

    // Plot title
    svg << "<text x=\"" << width / 2
        << "\" y=\"35\" text-anchor=\"middle\" "
        << "font-family=\"Arial\" font-size=\"22\">"
        << plot.title << "</text>\n";

    // Plot area axes
    const int left = margin;
    const int right = width - margin;
    const int top = margin;
    const int bottom = height - margin;

    svg << "<line x1=\"" << left << "\" y1=\"" << top
        << "\" x2=\"" << left << "\" y2=\"" << bottom
        << "\" stroke=\"black\"/>\n";

    svg << "<line x1=\"" << left << "\" y1=\"" << bottom
        << "\" x2=\"" << right << "\" y2=\"" << bottom
        << "\" stroke=\"black\"/>\n";

    // Axis labels
    svg << "<text x=\"" << width / 2
        << "\" y=\"" << height - 20
        << "\" text-anchor=\"middle\" "
        << "font-family=\"Arial\" font-size=\"16\">"
        << plot.x_label << "</text>\n";

    svg << "<text x=\"20\" y=\"" << height / 2
        << "\" text-anchor=\"middle\" "
        << "font-family=\"Arial\" font-size=\"16\" "
        << "transform=\"rotate(-90 20 " << height / 2 << ")\">"
        << plot.y_label << "</text>\n";

    // Find data ranges
    if (!plot.points.empty()) {
        double min_x = plot.points[0].x;
        double max_x = plot.points[0].x;
        double min_y = plot.points[0].y;
        double max_y = plot.points[0].y;

        for (const Point& point : plot.points) {
            min_x = std::min(min_x, point.x);
            max_x = std::max(max_x, point.x);
            min_y = std::min(min_y, point.y);
            max_y = std::max(max_y, point.y);
        }

        // Avoid division by zero for constant data
        if (min_x == max_x) {
            min_x -= 1.0;
            max_x += 1.0;
        }

        if (min_y == max_y) {
            min_y -= 1.0;
            max_y += 1.0;
        }

        // Draw data points
        for (const Point& point : plot.points) {
            double x = left +
                (point.x - min_x) / (max_x - min_x) * (right - left);

            double y = bottom -
                (point.y - min_y) / (max_y - min_y) * (bottom - top);

            svg << "<circle cx=\"" << std::fixed
                << std::setprecision(2) << x
                << "\" cy=\"" << y
                << "\" r=\"4\" fill=\"blue\"/>\n";
        }
    }

    svg << "</svg>\n";

    return svg.str();
}

bool Renderer::save_svg(const Plot& plot,
                        const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    file << render_svg(plot);
    return file.good();
}

} // namespace dataviz

