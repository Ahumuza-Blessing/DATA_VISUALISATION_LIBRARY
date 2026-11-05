#include "Renderer.hpp" // Includes the Renderer class declarations

#include "Axis.hpp" // Provides scaling and tick generation for graph axes

#include <algorithm> // Provides std::min and std::max
#include <iomanip>   // Provides std::fixed and std::setprecision
#include <sstream>   // Provides std::ostringstream for building SVG strings
#include <stdexcept> // Provides std::invalid_argument for input validation

namespace { // Anonymous namespace keeps these helpers local to this file

// Margins reserve space for titles, axis labels, and tick values.
constexpr double LEFT = 70.0;   // Left margin in SVG coordinate units
constexpr double RIGHT = 30.0;  // Right margin
constexpr double TOP = 55.0;    // Top margin
constexpr double BOTTOM = 70.0; // Bottom margin

// Creates the horizontal and vertical axis label elements.
std::string axisLabels(int width, int height,
                      const std::string& xLabel, const std::string& yLabel) {
    std::ostringstream svg; // Creates a stream for assembling SVG text

    // Places the horizontal axis label near the bottom center.
    svg << "<text x=\"" << width / 2 << "\" y=\"" << (height - 18)
        << "\" text-anchor=\"middle\" font-size=\"15\""
        << " font-family=\"sans-serif\">" << xLabel << "</text>\n";

    // Places the vertical axis label at the left, rotated by -90 degrees.
    svg << "<text x=\"22\" y=\"" << height / 2
        << "\" transform=\"rotate(-90 22 " << height / 2 << ")\""
        << " text-anchor=\"middle\" font-size=\"15\""
        << " font-family=\"sans-serif\">" << yLabel << "</text>\n";

    return svg.str(); // Returns both labels as an SVG string
}

// Converts a double into text with a controlled number of decimal places.
std::string number(double value, int precision = 2) {
    std::ostringstream out; // Creates a stream for number formatting
    out << std::fixed << std::setprecision(precision) << value;
    // std::fixed uses fixed-point notation.
    // std::setprecision controls digits after the decimal point.
    // For example, number(12.3456, 2) produces "12.35".
    return out.str(); // Returns the formatted number as a string
}
} // Ends the anonymous namespace

// Replaces special XML characters so text can safely appear inside SVG.
std::string Renderer::escapeXML(const std::string& text) {
    std::string result; // Stores the escaped output
    result.reserve(text.size()); // Reserves initial capacity to reduce reallocations

    for (char c : text) { // Examines every character in the input string
        switch (c) { // Selects a replacement based on the character
            case '&': result += "&amp;"; break;   // Escapes ampersands
            case '<': result += "&lt;"; break;    // Escapes less-than signs
            case '>': result += "&gt;"; break;    // Escapes greater-than signs
            case '"': result += "&quot;"; break; // Escapes double quotation marks
            case '\'': result += "&apos;"; break; // Escapes apostrophes
            default: result += c; break;          // Keeps ordinary characters unchanged
        }
    }

    return result; // Returns XML-safe text
}

// Generates the opening SVG tag and a white background.
std::string Renderer::svgStart(int width, int height) {
    if (width <= 0 || height <= 0) { // Rejects zero or negative dimensions
        throw std::invalid_argument("Renderer width and height must be positive.");
    }

    std::ostringstream svg; // Stores the opening SVG markup

    // Defines SVG dimensions and the coordinate system.
    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\""
        << width << "\" height=\"" << height
        << "\" viewBox=\"0 0 " << width << " " << height << "\">\n";

    // Adds a white rectangle covering the entire SVG background.
    svg << "<rect width=\"100%\" height=\"100%\" fill=\"white\"/>\n";

    return svg.str(); // Returns the SVG opening markup
}

// Generates the closing SVG tag.
std::string Renderer::svgEnd() {
    return "</svg>\n"; // Marks the end of the SVG document
}

// Converts category frequencies into an SVG count plot.
std::string Renderer::renderCountPlot(
    const CountPlot::Counts& counts, // Category names mapped to their frequencies
    int width,                       // SVG width
    int height,                      // SVG height
    const std::string& title,        // Graph title
    const Annotation& annotations,   // Additional graph text
    const std::string& xLabel,       // Horizontal axis label
    const std::string& yLabel        // Vertical axis label
) {
    if (counts.empty()) { // A count plot needs at least one category
        throw std::invalid_argument("Cannot render an empty count plot.");
    }
    if (width <= 0 || height <= 0) { // Checks that dimensions are positive
        throw std::invalid_argument("Renderer width and height must be positive.");
    }

    std::size_t maxCount = 1; // Starts at 1 to avoid a zero-length Axis range
    for (const auto& item : counts) { // Visits each category-count pair
        maxCount = std::max(maxCount, item.second); // Finds the largest count
    }

    // Defines the rectangular region available for drawing.
    const double plotLeft = LEFT;
    const double plotRight = width - RIGHT;
    const double plotTop = TOP;
    const double plotBottom = height - BOTTOM;

    // Creates a vertical axis mapping counts to SVG y coordinates.
    // SVG y coordinates increase downward, so the screen range is reversed.
    Axis yAxis(0.0, static_cast<double>(maxCount), plotBottom, plotTop);

    const double availableWidth = plotRight - plotLeft; // Horizontal drawing space
    const double slotWidth = availableWidth / static_cast<double>(counts.size());
    // Divides the available width equally among the categories.

    const double barWidth = slotWidth * 0.7;
    // Each bar occupies 70% of its slot, leaving space between bars.

    std::ostringstream svg; // Accumulates the SVG markup
    svg << svgStart(width, height); // Adds the SVG opening and background

    // Draws the graph title at the top center.
    svg << "<text x=\"" << width / 2
        << "\" y=\"30\" text-anchor=\"middle\" font-size=\"22\""
        << " font-family=\"sans-serif\">"
        << escapeXML(title) << "</text>\n";

    // Draws the horizontal baseline.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotBottom
        << "\" x2=\"" << plotRight << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    // Draws the vertical axis line.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotTop
        << "\" x2=\"" << plotLeft << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    std::size_t index = 0; // Tracks the horizontal slot for each category

    for (const auto& item : counts) { // Draws one bar for each category

        // Calculates the bar's left edge, centered inside its slot.
        const double x = plotLeft + index * slotWidth + (slotWidth - barWidth) / 2.0;

        // Converts the category count into a vertical SVG coordinate.
        const double y = yAxis.scale(static_cast<double>(item.second));

        // Calculates the visible height of the bar.
        const double barHeight = plotBottom - y;

        // Draws the rectangular bar using the calculated coordinates.
        svg << "<rect x=\"" << x << "\" y=\"" << y
            << "\" width=\"" << barWidth << "\" height=\"" << barHeight
            << "\" fill=\"steelblue\"/>\n";

        // Draws the category name below its bar.
        svg << "<text x=\"" << (x + barWidth / 2.0)
            << "\" y=\"" << (plotBottom + 20)
            << "\" text-anchor=\"middle\" font-size=\"12\""
            << " font-family=\"sans-serif\">"
            << escapeXML(item.first) << "</text>\n";

        // Draws the integer count just above the bar.
        svg << "<text x=\"" << (x + barWidth / 2.0)
            << "\" y=\"" << (y - 5)
            << "\" text-anchor=\"middle\" font-size=\"12\""
            << " font-family=\"sans-serif\">"
            << item.second << "</text>\n";

        ++index; // Moves to the next horizontal slot
    }

    // Generates and displays the vertical axis tick marks and labels.
    for (double tick : yAxis.ticks()) {
        const double y = yAxis.scale(tick); // Converts tick value to y coordinate

        // Draws a small tick line extending left of the vertical axis.
        svg << "<line x1=\"" << (plotLeft - 5) << "\" y1=\"" << y
            << "\" x2=\"" << plotLeft << "\" y2=\"" << y
            << "\" stroke=\"black\"/>\n";

        // Displays the tick value with one decimal place.
        svg << "<text x=\"" << (plotLeft - 10) << "\" y=\"" << (y + 4)
            << "\" text-anchor=\"end\" font-size=\"11\""
            << " font-family=\"sans-serif\">"
            << number(tick, 1) << "</text>\n";
    }

    // Adds any annotations supplied by the caller.
    for (const auto& note : annotations.getItems()) {
        svg << "<text x=\"" << note.x << "\" y=\"" << note.y
            << "\" font-size=\"13\" font-family=\"sans-serif\""
            << " fill=\"darkred\">"
            << escapeXML(note.text) << "</text>\n";
    }

    // Adds axis labels, closes the SVG, and returns the result.
    svg << axisLabels(width, height, escapeXML(xLabel), escapeXML(yLabel));
    svg << svgEnd();
    return svg.str();
}

// Converts histogram bins into an SVG histogram.
std::string Renderer::renderHistogram(
    const std::vector<HistogramBin>& bins, // Previously calculated histogram bins
    int width,                             // SVG width
    int height,                            // SVG height
    const std::string& title,              // Graph title
    const Annotation& annotations,         // Optional annotations
    const std::string& xLabel,             // Horizontal axis label
    const std::string& yLabel              // Vertical axis label
) {
    if (bins.empty()) { // Rejects an empty collection of bins
        throw std::invalid_argument("Cannot render an empty histogram.");
    }
    if (width <= 0 || height <= 0) { // Rejects invalid SVG dimensions
        throw std::invalid_argument("Renderer width and height must be positive.");
    }

    std::size_t maxCount = 1; // Ensures the vertical axis has a nonzero range
    for (const auto& bin : bins) { // Visits every histogram bin
        maxCount = std::max(maxCount, bin.count()); // Finds the maximum frequency
    }

    // Calculates the drawing boundaries.
    const double plotLeft = LEFT;
    const double plotRight = width - RIGHT;
    const double plotTop = TOP;
    const double plotBottom = height - BOTTOM;

    // Maps histogram frequencies to vertical SVG coordinates.
    Axis yAxis(0.0, static_cast<double>(maxCount), plotBottom, plotTop);

    const double availableWidth = plotRight - plotLeft; // Horizontal drawing space
    const double barWidth = availableWidth / static_cast<double>(bins.size());
    // Divides the horizontal space equally among the bins.

    std::ostringstream svg; // Creates the SVG output stream
    svg << svgStart(width, height); // Adds opening SVG markup

    // Draws the histogram title.
    svg << "<text x=\"" << width / 2
        << "\" y=\"30\" text-anchor=\"middle\" font-size=\"22\""
        << " font-family=\"sans-serif\">"
        << escapeXML(title) << "</text>\n";

    // Draws the horizontal axis line.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotBottom
        << "\" x2=\"" << plotRight << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    // Draws the vertical axis line.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotTop
        << "\" x2=\"" << plotLeft << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    // Draws each histogram bin as a rectangular bar.
    for (std::size_t i = 0; i < bins.size(); ++i) {
        const auto& bin = bins[i]; // Retrieves the current histogram bin
        const double x = plotLeft + i * barWidth; // Calculates bar position
        const double y = yAxis.scale(static_cast<double>(bin.count()));
        // Converts the bin frequency to a vertical coordinate.

        // Draws the bar; the white stroke separates neighboring bins.
        svg << "<rect x=\"" << x << "\" y=\"" << y
            << "\" width=\"" << barWidth
            << "\" height=\"" << (plotBottom - y)
            << "\" fill=\"seagreen\" stroke=\"white\"/>\n";

        // Displays the lower boundary of the bin with one decimal place.
        svg << "<text x=\"" << (x + barWidth / 2.0)
            << "\" y=\"" << (plotBottom + 18)
            << "\" text-anchor=\"middle\" font-size=\"10\""
            << " font-family=\"sans-serif\">"
            << number(bin.lower(), 1) << "</text>\n";
    }

    // Displays numerical tick labels along the vertical axis.
    for (double tick : yAxis.ticks()) {
        const double y = yAxis.scale(tick); // Calculates the tick position

        svg << "<text x=\"" << (plotLeft - 10) << "\" y=\"" << (y + 4)
            << "\" text-anchor=\"end\" font-size=\"11\""
            << " font-family=\"sans-serif\">"
            << number(tick, 1) << "</text>\n"; // Formats to one decimal place
    }

    // Draws the supplied annotations.
    for (const auto& note : annotations.getItems()) {
        svg << "<text x=\"" << note.x << "\" y=\"" << note.y
            << "\" font-size=\"13\" font-family=\"sans-serif\""
            << " fill=\"darkred\">"
            << escapeXML(note.text) << "</text>\n";
    }

    // Adds axis labels and finishes the SVG document.
    svg << axisLabels(width, height, escapeXML(xLabel), escapeXML(yLabel));
    svg << svgEnd();
    return svg.str();
}

// Converts estimated KDE points into an SVG density curve.
std::string Renderer::renderKDE(
    const std::vector<KDEPoint>& points, // Points containing x values and densities
    int width,                           // SVG width
    int height,                          // SVG height
    const std::string& title,            // Graph title
    const Annotation& annotations,       // Optional annotations
    const std::string& xLabel,           // Horizontal axis label
    const std::string& yLabel           // Vertical axis label
) {
    if (points.size() < 2) { // A KDE curve requires at least two points
        throw std::invalid_argument("KDE rendering needs at least two points.");
    }
    if (width <= 0 || height <= 0) { // Rejects invalid dimensions
        throw std::invalid_argument("Renderer width and height must be positive.");
    }

    // Initializes the data boundaries from the first point.
    double minX = points.front().x;
    double maxX = points.front().x;
    double maxDensity = points.front().density;

    for (const auto& point : points) { // Examines all KDE points
        minX = std::min(minX, point.x); // Finds the smallest x value
        maxX = std::max(maxX, point.x); // Finds the largest x value
        maxDensity = std::max(maxDensity, point.density); // Finds maximum density
    }

    if (minX == maxX) { // Avoids an Axis with equal minimum and maximum
        maxX = minX + 1.0; // Creates a nonzero horizontal range
    }
    if (maxDensity <= 0.0) { // Avoids a zero or negative vertical range
        maxDensity = 1.0; // Uses a positive fallback maximum
    }

    // Defines the available graph drawing area.
    const double plotLeft = LEFT;
    const double plotRight = width - RIGHT;
    const double plotTop = TOP;
    const double plotBottom = height - BOTTOM;

    // Creates horizontal and vertical axes for converting data into SVG positions.
    Axis xAxis(minX, maxX, plotLeft, plotRight);
    Axis yAxis(0.0, maxDensity, plotBottom, plotTop);

    std::ostringstream svg; // Accumulates SVG elements
    svg << svgStart(width, height); // Creates SVG opening and background

    // Draws the title at the top of the graph.
    svg << "<text x=\"" << width / 2
        << "\" y=\"30\" text-anchor=\"middle\" font-size=\"22\""
        << " font-family=\"sans-serif\">"
        << escapeXML(title) << "</text>\n";

    // Draws the horizontal axis.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotBottom
        << "\" x2=\"" << plotRight << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    // Draws the vertical axis.
    svg << "<line x1=\"" << plotLeft << "\" y1=\"" << plotTop
        << "\" x2=\"" << plotLeft << "\" y2=\"" << plotBottom
        << "\" stroke=\"black\"/>\n";

    // Starts an SVG polyline for connecting the KDE points.
    // fill="none" prevents filling the area below the curve.
    svg << "<polyline fill=\"none\" stroke=\"darkorange\""
        << " stroke-width=\"3\" points=\"";

    for (const auto& point : points) { // Processes each KDE point
        svg << xAxis.scale(point.x) << "," // Converts the x value to SVG x
            << yAxis.scale(point.density) << " "; // Converts density to SVG y
    }
    svg << "\"/>\n"; // Finishes the polyline element

    // Generates numerical labels for the horizontal axis.
    for (double tick : xAxis.ticks()) {
        const double x = xAxis.scale(tick); // Calculates horizontal tick position

        svg << "<text x=\"" << x << "\" y=\"" << (plotBottom + 20)
            << "\" text-anchor=\"middle\" font-size=\"11\""
            << " font-family=\"sans-serif\">"
            << number(tick, 1) << "</text>\n"; // Displays one decimal place
    }

    // Generates numerical labels for the vertical density axis.
    for (double tick : yAxis.ticks()) {
        const double y = yAxis.scale(tick); // Calculates vertical tick position

        svg << "<text x=\"" << (plotLeft - 10) << "\" y=\"" << (y + 4)
            << "\" text-anchor=\"end\" font-size=\"11\""
            << " font-family=\"sans-serif\">"
            << number(tick, 3) << "</text>\n"; // Displays three decimal places
    }

    // Adds annotations at their specified SVG coordinates.
    for (const auto& note : annotations.getItems()) {
        svg << "<text x=\"" << note.x << "\" y=\"" << note.y
            << "\" font-size=\"13\" font-family=\"sans-serif\""
            << " fill=\"darkred\">"
            << escapeXML(note.text) << "</text>\n";
    }

    // Adds axis labels, closes the SVG document, and returns its text.
    svg << axisLabels(width, height, escapeXML(xLabel), escapeXML(yLabel));
    svg << svgEnd();
    return svg.str();
}
