 Technical Report:
  Implementation and Testing of the Annotations Module

 1. Introduction

 This report explains how I implemented and tested the Annotations Module for the Data Visualization Library project in C++. The module is part of our CMP2103 Object-Oriented Programming group project.

The main purpose of the module is to allow users to add text labels to graphs at specific positions. For example, a user can label the starting point, highest point or final point on a graph to make the information easier to understand.

2. Design and Implementation

I divided the implementation into two files: `annotations.hpp` and `annotations.cpp`. The header file contains the class declarations, while the implementation file contains the actual function definitions.

The module consists of two main classes:

Annotation Class

This class represents one annotation on a graph. It stores three pieces of information:
- `x` – the horizontal position of the annotation.
- `y` – the vertical position of the annotation.
- `text` – the label to be displayed.

I used private member variables to protect the data and public getter functions (`getX()`, `getY()` and `getText()`) to access it.

Annotations Class

This class is used to manage several annotations at once. It uses a `std::vector<Annotation>` to store