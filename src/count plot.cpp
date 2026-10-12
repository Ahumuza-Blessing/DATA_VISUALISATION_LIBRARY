#include "dataviz/plot.hpp"

namespace dataviz {

Plot::Plot()
    : title_("Count Plot"),
      x_label_("Category"),
      y_label_("Count") {
}

void Plot::set_title(const std::string& title) {
    title_ = title;
}

void Plot::set_x_label(const std::string& label) {
    x_label_ = label;
}

void Plot::set_y_label(const std::string& label) {
    y_label_ = label;
}

void Plot::count_plot(const std::vector<std::string>& data) {
    counts_.clear();

    for (const std::string& category : data) {
        bool found = false;

        for (Count& item : counts_) {
            if (item.category == category) {
                ++item.frequency;
                found = true;
                break;
            }
        }

        if (!found) {
            counts_.push_back({category, 1});
        }
    }
}

const std::string& Plot::get_title() const {
    return title_;
}

const std::string& Plot::get_x_label() const {
    return x_label_;
}

const std::string& Plot::get_y_label() const {
    return y_label_;
}

const std::vector<Count>& Plot::get_counts() const {
    return counts_;
}

} // namespace dataviz
