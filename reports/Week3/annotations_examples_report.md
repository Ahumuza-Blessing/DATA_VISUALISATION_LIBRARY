# Technical Report: Implementation and Testing of the Annotations Module

## 1. Introduction

This report documents the design, implementation, and testing approach for the Annotations Module in the Data Visualization Library. The module is responsible for storing annotation text labels and their positions on a graph so that users can highlight important points such as the minimum, maximum, or final value.

The implementation was designed to be simple, reusable, and easy to integrate with rendering logic in the future. The code is structured around a lightweight data model that keeps each annotation item self-contained.

## 2. Requirements and Objectives

The annotation system was developed to satisfy the following goals:

- Store labels as text associated with graph coordinates.
- Support multiple annotations on the same graph.
- Keep the data model simple and easy to extend.
- Provide a clean interface for adding, retrieving, and clearing annotations.
- Separate the data structure from the rendering layer.

This design allows the library to remain modular while making it possible for a renderer or plotting component to later display each annotation visually.

## 3. Design Overview

The module is implemented using two core components:

### 3.1 AnnotationItem

The `AnnotationItem` structure represents one annotation on the graph. It contains:

- `x`: the horizontal coordinate
- `y`: the vertical coordinate
- `text`: the label associated with that point

This structure keeps the text and position together, which is useful when a renderer later draws the annotation at the correct location.

### 3.2 Annotation

The `Annotation` class acts as a container for multiple `AnnotationItem` objects. It stores the items in a `std::vector<AnnotationItem>`, which allows the library to:

- append new annotation entries
- remove all entries when needed
- return the entire collection for later processing

The class exposes a minimal public interface:

- `add(double x, double y, const std::string& text)`
- `clear()`
- `getItems() const`

This keeps the module easy to use while preserving encapsulation of the internal data.

## 4. Implementation Details

The implementation is split into a header file and a source file:

- `annotations.hpp` contains the class and struct declarations
- `annotations.cpp` contains the logic for each member function

### 4.1 Header File

The class definition includes the necessary standard library headers:

- `<string>` for text handling
- `<vector>` for storing annotation items

The `AnnotationItem` struct is declared first because it defines the basic data type used inside the `Annotation` class.

### 4.2 Add Function

The `add` method appends a new `AnnotationItem` into the vector using the values passed in by the caller:

- x-coordinate
- y-coordinate
- text label

This method stores annotation data in the order they are added, which is useful for consistent rendering and later iteration.

### 4.3 Clear Function

The `clear` method removes all stored annotation items by calling `items.clear()`. This resets the annotation list and allows the application to start a fresh set of labels.

### 4.4 Get Items Function

The `getItems` function returns a constant reference to the vector. This provides read-only access to the stored data without exposing the internal list for modification.

## 5. Data Model

The annotation data model is intentionally simple:

```cpp
struct AnnotationItem {
    double x;
    double y;
    std::string text;
};
```