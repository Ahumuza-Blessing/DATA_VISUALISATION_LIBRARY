#include "countplot.hpp"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace dataviz {

CountPlot::CountPlot()
    : title_("Count Plot"),
      x_label_("Category"),
      y_label_("Count") {
}

void CountPlot::set_title(const std::string& title) {
    title_ = title;
}

void CountPlot::set_x_label(const std::string& label) {
    x_label_ = label;
}

void CountPlot::set_y_label(const std::string& label) {
    y_label_ = label;
}

void CountPlot::count(const std::vector<std::string>& data) {
    counts_.clear();

    // Maps a category to its position in counts_, so each lookup is fast
    // while the first-appearance order is kept.
    std::unordered_map<std::string, std::size_t> index;

    for (const std::string& category : data) {
        auto it = index.find(category);

        if (it == index.end()) {
            index[category] = counts_.size();
            counts_.push_back({category, 1});
        } else {
            ++counts_[it->second].frequency;
        }
    }
}

const std::string& CountPlot::get_title() const {
    return title_;
}

const std::string& CountPlot::get_x_label() const {
    return x_label_;
}

const std::string& CountPlot::get_y_label() const {
    return y_label_;
}

const std::vector<Count>& CountPlot::get_counts() const {
    return counts_;
}

std::vector<std::string> CountPlot::categories() const {
    std::vector<std::string> result;
    result.reserve(counts_.size());
    for (const Count& item : counts_) {
        result.push_back(item.category);
    }
    return result;
}

std::vector<std::size_t> CountPlot::frequencies() const {
    std::vector<std::size_t> result;
    result.reserve(counts_.size());
    for (const Count& item : counts_) {
        result.push_back(item.frequency);
    }
    return result;
}

std::size_t CountPlot::max_frequency() const {
    std::size_t highest = 0;
    for (const Count& item : counts_) {
        highest = std::max(highest, item.frequency);
    }
    return highest;
}

std::size_t CountPlot::total() const {
    std::size_t sum = 0;
    for (const Count& item : counts_) {
        sum += item.frequency;
    }
    return sum;
}

} // namespace dataviz