
#ifndef ANNOTATIONS_HPP
#define ANNOTATIONS_HPP

#include <string>
#include <vector>

namespace dataviz {

// Represents one text annotation on a graph
class Annotation {
private:
    double x;
    double y;
    std::string text;

public:
    // Constructor
    Annotation(double xPosition, double yPosition,
               const std::string& annotationText);

    // Accessor functions
    double getX() const;
    double getY() const;
    std::string getText() const;
};

// Manages multiple annotations
class Annotations {
private:
    std::vector<Annotation> annotations;

public:
    // Add an annotation
    void add(const Annotation& annotation);

    // Get all annotations
    const std::vector<Annotation>& getAll() const;

    // Check whether there are no annotations
    bool empty() const;

    // Remove all annotations
    void clear();
};

} // namespace dataviz

#endif // ANNOTATIONS_HPP
