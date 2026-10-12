#ifndef DATAVIZ_PLOT_HPP
#define DATAVIZ_PLOT_HPP

#include <string>
#include <vector>

namespace dataviz {

struct Count {
    std::string category;
    int frequency;
};

class Plot {
public:
    Plot();

    void set_title(const std::string& title);
    void set_x_label(const std::string& label);
    void set_y_label(const std::string& label);

    void count_plot(const std::vector<std::string>& data);

    const std::string& get_title() const;
    const std::string& get_x_label() const;
    const std::string& get_y_label() const;

    const std::vector<Count>& get_counts() const;

private:
    std::string title_;
    std::string x_label_;
    std::string y_label_;
    std::vector<Count> counts_;
};

} // namespace dataviz

#endif // DATAVIZ_PLOT_HPP
