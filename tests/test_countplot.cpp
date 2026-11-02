#include "CountPlot.hpp"
#include <cassert>
#include <iostream>
int main() {
    auto counts = CountPlot::calculate({"A", "B", "A", "", "C", "A"});
    assert(counts.size() == 3);
    assert(counts.at("A") == 3);
    assert(counts.at("B") == 1);
    assert(counts.find("") == counts.end());
    assert(CountPlot::calculate({}).empty());
    std::cout << "CountPlot tests passed.\n";
}
