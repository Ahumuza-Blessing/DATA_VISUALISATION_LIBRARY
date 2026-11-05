#ifndef ANNOTATION_HPP // Checks whether this header has already been included
#define ANNOTATION_HPP // Defines the header guard to prevent repeated inclusion

#include <string> // Provides std::string for storing annotation text
#include <vector> // Provides std::vector for storing multiple annotations

// I want to keep the text and position of each note together.
// Later, the Renderer can place these notes on the graph.

// A structure that groups the position and text of one annotation.
struct AnnotationItem {
    double x;         // Horizontal position where the annotation will appear
    double y;         // Vertical position where the annotation will appear
    std::string text; // The message or label displayed on the graph
};

// Manages annotations that can be added to a graph.
class Annotation {
private: // Members accessible only inside the Annotation class

    // The rest of the library will use this public interface.
    std::vector<AnnotationItem> items;
    // Stores all annotation items in the order they were added.
    // Each item contains an x coordinate, y coordinate, and text.

public: // Functions that other parts of the library can access

    // Adds a new annotation with its position and text.
    // const std::string& avoids copying the string and prevents modification.
    void add(double x, double y, const std::string& text);

    // Removes all annotations currently stored in the vector.
    void clear();

    // Returns a read-only reference to the stored annotations.
    // The final const means this function does not modify the Annotation object.
    const std::vector<AnnotationItem>& getItems() const;
};

#endif // Ends the header guard