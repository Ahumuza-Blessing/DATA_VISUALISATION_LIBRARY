#include "Histogram.hpp"
#include <cassert>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <type_traits>

int main() {
    static_assert(!std::is_copy_assignable_v<HistogramBin>);
    static_assert(!std::is_move_assignable_v<HistogramBin>);

    // This checks the same even-range counting behavior as the earlier
    // constructor implementation, through the new build() interface.
    
    auto bins = Histogram::build({1, 2, 3, 4}, 2);
    assert(bins.size() == 2);
    assert(bins[0].count() == 2 && bins[1].count() == 2);
    assert(bins[0].lower() == 1 && bins[0].upper() == 2.5);

    // Unlike the earlier constructor, identical values now produce one
    // zero-width bin rather than the requested number of widened bins.
    
    auto same = Histogram::build({5, 5, 5}, 4);
    assert(same.size() == 1 && same[0].count() == 3);
    assert(same[0].lower() == 5 && same[0].upper() == 5);

    // A zero bin count remains invalid, as it was in the earlier constructor.
    
    bool threw = false;
    try { Histogram::build({1, 2}, 0); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    // Reject NaN and both signs of infinity before calculating bins.
    threw = false;
    try { Histogram::build({1, std::numeric_limits<double>::quiet_NaN()}, 2); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    threw = false;
    try { Histogram::build({1, std::numeric_limits<double>::infinity()}, 2); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    threw = false;
    try { Histogram::build({1, -std::numeric_limits<double>::infinity()}, 2); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);

    std::cout << "Histogram tests passed.\n";
}