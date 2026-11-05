#include "Annotation.hpp" // Provides notes for the rendered chart.
#include "DataLoader.hpp" // Loads the example CSV data.
#include "DataProcessor.hpp" // Cleans rows and extracts numeric marks.
#include "Histogram.hpp" // Groups marks into histogram bins.
#include "ImageExporter.hpp" // Saves the rendered SVG.
#include "Renderer.hpp" // Converts histogram bins into SVG markup.
#include "Statistics.hpp" // Calculates the summary statistics shown.

#include <exception> // Handles errors from loading and rendering.
#include <iomanip> // Limits displayed statistics to four decimal places.
#include <iostream> // Prints statistics and example status.
#include <sstream> // Builds formatted statistic strings.
#include <string> // Stores labels and formatted output.
#include <vector> // Holds loaded data and mode values.

namespace { // Keeps the formatting helper private to this example.

// Formats a statistic with up to four decimal places and no trailing zeros.
std::string formatStatistic(double value) { // Converts one value to concise decimal text.
    std::ostringstream formatted; // Creates a string stream for numeric formatting.
    formatted << std::fixed << std::setprecision(4) << value; // Rounds output to at most four decimal places.

    std::string result = formatted.str(); // Copies the formatted value into a string.
    result.erase(result.find_last_not_of('0') + 1, std::string::npos); // Removes fractional trailing zeros.
    if (!result.empty() && result.back() == '.') { // Checks for a decimal point left at the end.
        result.pop_back(); // Removes the now-unneeded decimal point.
    } // Ends decimal-point cleanup.
    return result; // Returns the concise formatted value.
} // Ends formatStatistic.

} // Ends the helper's anonymous namespace.

// Loads sample marks, prints their summary, and saves a histogram SVG.
int main() { // Starts the standalone histogram example.
    try { // Handles failures from data loading or chart generation.
        // First read the marks from our sample CSV and turn them into numbers.
        auto rows = DataProcessor::cleanRows( // Cleans the CSV rows after loading them.
            DataLoader::loadCSV("data/input/student_marks.csv")); // Reads the sample student data.
        auto marks = DataProcessor::toNumeric(DataProcessor::getColumn(rows, 2)); // Extracts the Mark column as numbers.

        const auto modes = Statistics::mode(marks); // Finds all most-frequent marks.
        const double firstQuartile = Statistics::firstQuartile(marks); // Calculates the lower quartile.
        const double thirdQuartile = Statistics::thirdQuartile(marks); // Calculates the upper quartile.
        const double variance = Statistics::variance(marks); // Calculates population variance.
        const double standardDeviation = Statistics::standardDeviation(marks); // Calculates spread in the original units.

        std::cout << "Mode(s): "; // Begins printing the modes summary.
        if (modes.empty()) { // Checks whether any mark occurs more than once.
            std::cout << "none"; // Reports that the dataset has no mode.
        } else { // Handles one or more modes.
            for (std::size_t i = 0; i < modes.size(); ++i) { // Visits each mode in order.
                if (i > 0) { // Checks whether a prior mode was printed.
                    std::cout << ", "; // Separates multiple modes with commas.
                } // Ends the separator check.
                std::cout << formatStatistic(modes[i]); // Prints this mode using the chosen precision.
            } // Ends mode output.
        } // Ends the mode/no-mode choice.
        std::cout << "\nMean: " << formatStatistic(Statistics::mean(marks)) // Prints the arithmetic mean.
                  << "\nFirst quartile (Q1): " << formatStatistic(firstQuartile) // Prints the lower quartile.
                  << "\nThird quartile (Q3): " << formatStatistic(thirdQuartile) // Prints the upper quartile.
                  << "\nInterquartile range (IQR): " // Begins the IQR label.
                  << formatStatistic(Statistics::interquartileRange(marks)) // Prints the difference between quartiles.
                  << "\nPopulation variance: " << formatStatistic(variance) // Prints population variance.
                  << "\nStandard deviation: " // Begins the standard-deviation label.
                  << formatStatistic(standardDeviation) << "\n"; // Prints standard deviation and ends the output line.

        // The histogram module groups the marks; the Renderer does the drawing.
        auto bins = Histogram::build(marks, 5); // Divides the marks into five bins.
        Annotation notes; // Creates the collection of chart annotations.
        std::string modeLabel = "Mode(s): "; // Initializes the chart's mode label.
        if (modes.empty()) { // Checks whether the mode list is empty.
            modeLabel += "none"; // Adds the no-mode description.
        } else { // Handles datasets with one or more modes.
            for (std::size_t i = 0; i < modes.size(); ++i) { // Visits each mode for the chart label.
                if (i > 0) { // Checks if this is not the first mode.
                    modeLabel += ", "; // Adds a separator before additional modes.
                } // Ends separator handling.
                modeLabel += formatStatistic(modes[i]); // Appends the current formatted mode.
            } // Ends mode-label construction.
        } // Ends the mode/no-mode choice for the chart.

        notes.add(520, 78, "Mean mark: " + formatStatistic(Statistics::mean(marks))); // Places the mean annotation.
        notes.add(520, 96, modeLabel); // Places the mode annotation below the mean.
        notes.add(520, 114, "Q1: " + formatStatistic(firstQuartile)); // Places the first-quartile annotation.
        notes.add(520, 132, "Q3: " + formatStatistic(thirdQuartile)); // Places the third-quartile annotation.
        notes.add(520, 150, "IQR: " + formatStatistic( // Begins adding the interquartile-range annotation.
            Statistics::interquartileRange(marks))); // Calculates and formats the IQR value.
        notes.add(520, 168, "Variance: " + formatStatistic(variance)); // Places the variance annotation.
        notes.add(520, 186, "Std. deviation: " + formatStatistic(standardDeviation)); // Places the standard-deviation annotation.

        std::string svg = Renderer::renderHistogram( // Creates SVG markup from the bins and notes.
            bins, 800, 500, "Student Marks Histogram", notes, "Mark", "Frequency"); // Supplies chart dimensions, title, and axis labels.
        ImageExporter::saveSVG(svg, "histogram_example.svg"); // Writes the histogram chart to the output directory.

        std::cout << "Created " << ImageExporter::outputFile("histogram_example.svg") << " with " // Starts reporting the saved chart path.
                  << bins.size() << " bins.\n"; // Prints how many bins the chart contains.
    } catch (const std::exception& error) { // Catches standard exceptions from the example operations.
        std::cerr << "Histogram example failed: " << error.what() << "\n"; // Reports the failure reason.
        return 1; // Signals unsuccessful example execution.
    } // Ends exception handling.
    return 0; // Signals successful example execution.
} // Ends the standalone histogram example.