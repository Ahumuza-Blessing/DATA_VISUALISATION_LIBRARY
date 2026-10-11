

#ifndef DATAVIZ_RENDERER_HPP
#define DATAVIZ_RENDERER_HPP

#include <string>
#include <vector>

namespace dataviz {

struct Point {
    double x;
    double y;
};

struct PlotOptions {
    std::string title = "Plot";
    std::string xLabel = "X";
    std::string yLabel = "Y";
    int width = 800;
    int height = 600;
};

class Renderer {
public:
    void linePlot(
        const std::vector<Point>& points,
        const PlotOptions& options,
        const std::string& filename
    );

    void histogram(
        const std::vector<double>& data,
        int bins,
        const PlotOptions& options,
        const std::string& filename
    );

    void countPlot(
        const std::vector<std::string>& categories,
        const PlotOptions& options,
        const std::string& filename
    );

    void kdePlot(
        const std::vector<double>& data,
        const PlotOptions& options,
        const std::string& filename
    );
}

} // namespace dataviz

#endif
