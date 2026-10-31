#include <iostream>
#include <cassert>
#include "annotations.hpp"

void test_annotations() {
    dataviz::Annotations annotations;

    // 1. Test initial empty state
    assert(annotations.empty() == true);
    std::cout << "Test 1 Passed: Collection is initially empty." << std::endl;

    // 2. Add annotations and verify collection size/contents
    annotations.add(dataviz::Annotation(1.0, 2.0, "Starting Point"));
    annotations.add(dataviz::Annotation(2.0, 4.0, "Highest Point"));
    annotations.add(dataviz::Annotation(3.0, 3.0, "Final Point"));

    assert(annotations.empty() == false);
    auto all_annotations = annotations.getAll();
    assert(all_annotations.size() == 3);
    std::cout << "Test 2 Passed: Annotations added successfully, count is 3." << std::endl;

    // 3. Verify specific data values
    assert(all_annotations[0].getText() == "Starting Point");
    assert(all_annotations[1].getY() == 4.0);
    std::cout << "Test 3 Passed: Annotation data fields are correct." << std::endl;

    // 4. Test clearing the collection
    annotations.clear();
    assert(annotations.empty() == true);
    std::cout << "Test 4 Passed: Collection cleared successfully." << std::endl;
}

int main() {
    std::cout << "Running Annotations Unit Tests..." << std::endl;
    test_annotations();
    std::cout << "All Annotations tests passed successfully!" << std::endl;
    return 0;
}