#include "Annotation.hpp" // Includes the Annotation class being tested
#include <cassert>        // Provides assert() for checking expected conditions
#include <iostream>       // Provides std::cout for displaying test results

int main() { // Entry point of the Annotation test program

    // Creates an Annotation object to store graph notes.
    Annotation annotations;

    // Checks that a newly created Annotation object contains no items.
    // empty() returns true when the vector has no elements.
    assert(annotations.getItems().empty());

    // Adds an annotation named "Peak" at position (10, 20).
    annotations.add(10, 20, "Peak");

    // Adds another annotation named "Average" at position (30, 40).
    annotations.add(30, 40, "Average");

    // Verifies that exactly two annotations have been stored.
    // size() returns the number of elements in the vector.
    assert(annotations.getItems().size() == 2);

    // Checks that the first annotation contains the text "Peak".
    // [0] accesses the first element because C++ indexing starts at zero.
    assert(annotations.getItems()[0].text == "Peak");

    // Checks that the second annotation has an x coordinate of 30.
    // [1] accesses the second element.
    assert(annotations.getItems()[1].x == 30);

    // Removes all stored annotations.
    annotations.clear();

    // Verifies that the vector is empty after calling clear().
    assert(annotations.getItems().empty());

    // Displays a success message if all enabled assertions pass.
    std::cout << "Annotation tests passed.\n";
}