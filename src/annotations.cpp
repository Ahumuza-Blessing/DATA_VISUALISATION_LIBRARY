
#include "Annotations.hpp"

namespace dataviz {

// Implement the Annotation constructor
Annotation::Annotation(double xPosition, double yPosition,
                       const std::string& annotationText)
    : x(xPosition), y(yPosition), text(annotationText) {
}

// Return the x-coordinate
double Annotation::getX() const {
    return x;
}

// Return the y-coordinate
double Annotation::getY() const {
    return y;
}

// Return the annotation text
std::string Annotation::getText() const {
    return text;
}

// Add an annotation to the collection
void Annotations::add(const Annotation& annotation) {
    annotations.push_back(annotation);
}

// Return all stored annotations
const std::vector<Annotation>& Annotations::getAll() const {
    return annotations;
}

// Check whether the collection is empty
bool Annotations::empty() const {
    return annotations.empty();
}

// Remove all annotations
void Annotations::clear() {
    annotations.clear();
}

} // namespace dataviz
