#ifndef DATAVIZ_COUNTPLOT_HPP
#define DATAVIZ_COUNTPLOT_HPP

#include <cstddef>  // std::size_t
#include <string>   // std::string
#include <vector>   // std::vector

namespace dataviz {

// One category and how many times it appeared in the input.
struct Count {
    std::string category;
    std::size_t frequency;
};

// Counts how many times each distinct category appears in a dataset.
// This class only does the counting. Drawing the bars is done by Renderer.
class CountPlot {
public:
    CountPlot();

    void set_title(const std::string& title);
    void set_x_label(const std::string& label);
    void set_y_label(const std::string& label);

    // Counts each distinct category in data. Clears any previous result.
    // Categories are stored in the order they first appear.
    // An empty input gives an empty result (no error).
    void count(const std::vector<std::string>& data);

    const std::string& get_title() const;
    const std::string& get_x_label() const;
    const std::string& get_y_label() const;

    // Category/frequency pairs in order of first appearance.
    const std::vector<Count>& get_counts() const;

    // Convenience views for the renderer (same order as get_counts()).
    std::vector<std::string> categories() const;
    std::vector<std::size_t> frequencies() const;

    // Highest frequency (0 if nothing has been counted). Useful for
    // scaling the y-axis.
    std::size_t max_frequency() const;

    // Total number of items counted.
    std::size_t total() const;

private:
    std::string title_;
    std::string x_label_;
    std::string y_label_;
    std::vector<Count> counts_;
};

} // namespace dataviz

#endif // DATAVIZ_COUNTPLOT_HPP