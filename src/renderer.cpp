
#include "../include/dataviz/renderer.hpp"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <map>
#include <stdexcept>

namespace dataviz {

namespace {
void startSvg(std::ofstream& out, const PlotOptions& options) {
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" "
        << "width=\"" << options.width << "\" "
        << "height=\"" << options.height << "\">\n";

    out << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";
    out << "<text x=\"" << options.width / 2
        << "\" y=\"30\" text-anchor=\"middle\" font-size=\"20\">"
        << options.title << "</text>\n";
}

void endSvg(std::ofstream& out) {
    out << "</svg>\n";
}
}

void Renderer::linePlot(
    const std::vector<Point>& points,
    const PlotOptions& options,
    const std::string& filename) {

    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open output file");

    startSvg(out, options);

    if (!points.empty()) {
        double minX = points[0].x, maxX = points[0].x;
        double minY = points[0].y, maxY = points[0].y;

        for (const auto& p : points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }

        if (maxX == minX) maxX = minX + 1;
        if (maxY == minY) maxY = minY + 1;

        out << "<polyline fill=\"none\" stroke=\"blue\" "
            << "stroke-width=\"2\" points=\"";

        for (const auto& p : points) {
            double x = 60 + (p.x - minX) / (maxX - minX)
                           * (options.width - 100);
            double y = options.height - 50
                       - (p.y - minY) / (maxY - minY)
                       * (options.height - 100);
            out << x << "," << y << " ";
        }
        out << "\"/>\n";
    }

    endSvg(out);
}

void Renderer::histogram(
    const std::vector<double>& data,
    int bins,
    const PlotOptions& options,
    const std::string& filename) {

    if (bins <= 0) throw std::invalid_argument("Bins must be positive");

    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open output file");

    startSvg(out, options);

    if (!data.empty()) {
        double low = *std::min_element(data.begin(), data.end());
        double high = *std::max_element(data.begin(), data.end());
        if (high == low) high = low + 1;

        std::vector<int> counts(bins, 0);
        for (double value : data) {
            int index = static_cast<int>(
                (value - low) / (high - low) * bins);
            if (index >= bins) index = bins - 1;
            if (index < 0) index = 0;
            counts[index]++;
        }

        int maxCount = *std::max_element(counts.begin(), counts.end());
        double barWidth = (options.width - 100.0) / bins;

        for (int i = 0; i < bins; ++i) {
            double h = maxCount == 0 ? 0 :
                counts[i] / static_cast<double>(maxCount)
                * (options.height - 100);

            out << "<rect x=\"" << 50 + i * barWidth
                << "\" y=\"" << options.height - 50 - h
                << "\" width=\"" << barWidth - 2
                << "\" height=\"" << h
                << "\" fill=\"steelblue\"/>\n";
        }
    }

    endSvg(out);
}

void Renderer::countPlot(
    const std::vector<std::string>& categories,
    const PlotOptions& options,
    const std::string& filename) {

    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open output file");

    startSvg(out, options);

    std::map<std::string, int> counts;
    for (const auto& category : categories) counts[category]++;

    int maxCount = 1;
    for (const auto& item : counts)
        maxCount = std::max(maxCount, item.second);

    int i = 0;
    double rowHeight = counts.empty() ? 0 :
        (options.height - 70.0) / counts.size();

    for (const auto& item : counts) {
        double width = item.second / static_cast<double>(maxCount)
                       * (options.width - 160);

        double y = 50 + i * rowHeight;
        out << "<text x=\"10\" y=\"" << y + rowHeight / 2
            << "\" font-size=\"12\">" << item.first << "</text>\n";
        out << "<rect x=\"120\" y=\"" << y
            << "\" width=\"" << width
            << "\" height=\"" << rowHeight - 3
            << "\" fill=\"orange\"/>\n";
        ++i;
    }

    endSvg(out);
}

void Renderer::kdePlot(
    const std::vector<double>& data,
    const PlotOptions& options,
    const std::string& filename) {

    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Cannot open output file");

    startSvg(out, options);

    if (data.size() >= 2) {
        double low = *std::min_element(data.begin(), data.end());
        double high = *std::max_element(data.begin(), data.end());
        if (high == low) high = low + 1;

        double mean = 0;
        for (double v : data) mean += v;
        mean /= data.size();

        double variance = 0;
        for (double v : data) variance += (v - mean) * (v - mean);
        variance /= data.size();

        double bandwidth = 1.06 * std::sqrt(variance)
                           * std::pow(data.size(), -0.2);
        if (bandwidth <= 0) bandwidth = (high - low) / 10;

        std::vector<double> densities;
        for (int i = 0; i <= 100; ++i) {
            double xValue = low + (high - low) * i / 100.0;
            double density = 0;

            for (double v : data) {
                double z = (xValue - v) / bandwidth;
                density += std::exp(-0.5 * z * z);
            }

            density /= data.size() * bandwidth
                       * std::sqrt(2 * 3.141592653589793);
            densities.push_back(density);
        }

        double maxDensity = *std::max_element(
            densities.begin(), densities.end());
        if (maxDensity <= 0) maxDensity = 1;

        out << "<polyline fill=\"none\" stroke=\"red\" "
            << "stroke-width=\"2\" points=\"";

        for (int i = 0; i <= 100; ++i) {
            double x = 50 + i / 100.0 * (options.width - 100);
            double y = options.height - 50
                - densities[i] / maxDensity * (options.height - 100);
            out << x << "," << y << " ";
        }

        out << "\"/>\n";
    }

    endSvg(out);
}

} // namespace dataviz

