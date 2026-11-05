#include "CountPlot.hpp" // Includes the CountPlot class we want to test
#include <cassert>       // Provides assert() for checking test conditions
#include <iostream>      // Provides std::cout for displaying messages

int main() { // The test program begins execution here

    // Calls the static calculate() function using the class name.
    //
    // We pass six strings:
    // "A", "B", "A", "", "C", "A"
    //
    // Expected results:
    // A = 3
    // B = 1
    // C = 1
    //
    // The empty string should be ignored.
    auto counts = CountPlot::calculate({"A", "B", "A", "", "C", "A"});

    // Checks that the map contains exactly three different categories.
    // The empty string should not be counted as a category.
    assert(counts.size() == 3);

    // Checks that category A appears exactly three times.
    // .at("A") retrieves the count stored under key "A".
    assert(counts.at("A") == 3);

    // Checks that category B appears exactly once.
    assert(counts.at("B") == 1);

    // Checks that an empty category does not exist in the map.
    //
    // .find("") searches for an empty-string key.
    // .end() represents the position after the final map element.
    //
    // If find() returns end(), the key was not found.
    assert(counts.find("") == counts.end());

    // Calls calculate() with an empty vector.
    //
    // An empty input should produce an empty map.
    // .empty() returns true if the map contains no entries.
    assert(CountPlot::calculate({}).empty());

    // Displays a success message if all enabled assertions pass.
    std::cout << "CountPlot tests passed.\n";
}
