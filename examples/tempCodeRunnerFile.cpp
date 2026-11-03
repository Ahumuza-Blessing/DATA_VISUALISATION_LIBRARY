
#include <iostream>
#include "Annotations.hpp"

int main() {

    // Create an annotation collection
    dataviz::Annotations annotations;

    // Check whether the collection is initially empty
    std::cout << "Initial collection: ";

    if (annotations.empty()) {
        std::cout << "Empty" << std::endl;
    }

    // Create three annotations
    dataviz::Annotation annotation1(1.0, 2.0, "Starting Point");
    dataviz::Annotation annotation2(2.0, 4.0, "Highest Point");
    dataviz::Annotation annotation3(3.0, 3.0, "Final Point");

    // Add annotations to the collection
    annotations.add(annotation1);
    annotations.add(annotation2);
    annotations.add(annotation3);

    // Display all annotations
    std::cout << "\nANNOTATIONS ON GRAPH\n";
    std::cout << "--------------------\n";

    for (const dataviz::Annotation& annotation : annotations.getAll()) {

        std::cout << "Label: " << annotation.getText() << std::endl;

        std::cout << "X-coordinate: "
                  << annotation.getX() << std::endl;

        std::cout << "Y-coordinate: "
                  << annotation.getY() << std::endl;

        std::cout << std::endl;
    }

    // Display the total number of annotations
    std::cout << "Total annotations: "
              << annotations.getAll().size() << std::endl;

    // Remove all annotations
    annotations.clear();

    // Verify that the collection is empty
    std::cout << "\nAfter clearing: ";

    if (annotations.empty()) {
        std::cout << "Annotation collection is empty."
                  << std::endl;
    }

    return 0;