#include "Histogram.hpp"
#include <cassert>
#include <iostream>
#include <stdexcept>

int main() {
    // This checks the same even-range counting behavior as the earlier
    // constructor implementation, through the new build() interface.
    
    auto bins = Histogram::build({1, 2, 3, 4}, 2);
    assert(bins.size() == 2);
    assert(bins[0].count == 2 && bins[1].count == 2);

    // Unlike the earlier constructor, identical values now produce one
    // zero-width bin rather than the requested number of widened bins.
    
    auto same = Histogram::build({5, 5, 5}, 4);
    assert(same.size() == 1 && same[0].count == 3);

    // A zero bin count remains invalid, as it was in the earlier constructor.
    
    bool threw = false;
    try { Histogram::build({1, 2}, 0); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    std::cout << "Histogram tests passed.\n";
}