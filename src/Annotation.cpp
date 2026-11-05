#include "Annotation.hpp" // Includes the Annotation class and AnnotationItem structure declarations

// I keep the notes in the order they were added to the graph.
void Annotation::add(double x, double y, const std::string& text) {
    // Annotation::add identifies this function as belonging to the Annotation class.
    // x and y represent the position of the annotation.
    // text contains the message that will appear on the graph.

    // Creates an AnnotationItem using x, y, and text.
    // push_back() adds the new item to the end of the vector.
    items.push_back({x, y, text});
}

// Removes all annotations from the object.
void Annotation::clear() {
    // clear() removes every element currently stored in the vector.
    // The Annotation object itself remains available for reuse.
    items.clear();
}

// Returns the stored annotations without allowing callers to modify them.
const std::vector<AnnotationItem>& Annotation::getItems() const {
    // const prevents callers from modifying the returned vector through this reference.
    // & returns a reference instead of making a copy of the entire vector.
    // The const after the parentheses means this function does not modify the object.
    return items;
}