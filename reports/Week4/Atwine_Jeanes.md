IMPLEMENTATION REPORT
Project Title: Development of a Data Visualization Library in C++  
Student Name: Atwine Jeanes  
Module: Data Processing  


 1. Introduction

This report focuses on implementing the modules designed during last week's report. My responsibility is the Data Processing module, which prepares numerical data for use by the Statistics and Plotting components of the C++ Data Visualization Library.

2. Objectives

The objectives of this part is to implement the data-processing functions, handle invalid numerical values, ensure compatibility with other modules, and prepare the implementation for testing and integration.

3. Implementation Activities

Following the creation of the header file in Phase 1, the implementation was prepared in `DataProcessing.cpp`. The module is designed to provide the following functions:

 Function                       Description
isEmpty()                  Checks whether a dataset is empty. 
validateData()             Checks whether a dataset is valid. 
cleanData()                 Removes non-finite numerical values. 
normalizeData()             Scales values to a range between 0 and 1. 
findMinimum()                Identifies the smallest value. 
findMaximum()                Identifies the largest value. 

Normalization uses the minimum-maximum formula:

The implementation also considers empty datasets, invalid numerical values, and datasets whose values are all equal to prevent division by zero.

4. Application of Object-Oriented Programming Concepts

a).Encapsulation
Encapsulation combines data and related functions within a class and controls access using `private`, `public`, and `protected` access specifiers. In the Data Visualization Library, it can protect internal data while providing public functions for accessing or modifying it. My module also separates its function declarations in the header file from their definitions in the source file, supporting modularity. However, this separation alone does not constitute class-based encapsulation.

b). Inheritance
Inheritance allows a derived class to reuse and extend accessible members of a base class. In the library, a common plotting class could provide shared functionality for specialized classes such as `Histogram` and `KDEPlot`, provided this inheritance relationship is implemented in the actual code.

c).Polymorphism
Polymorphism allows different classes to provide different implementations of a common interface. For example, plotting classes could override a virtual `render()` function to generate different visualizations. The use of inheritance and polymorphism must be supported by the actual class definitions in the project.

 5. Module Integration
The Data Processing module is intended to prepare numerical data for statistical analysis and plotting. Its functions support data validation, cleaning, and normalization before the processed data is used by other components. This separation of responsibilities promotes code reuse and simplifies maintenance.

6. Challenges and Considerations
The main considerations include handling invalid data, preventing division by zero, ensuring consistency between the header and source files, and maintaining compatibility with other modules. Testing will be necessary to verify that the functions behave as expected.

 7. Class-Layout Diagrams
Class-layout diagrams will be drawn on paper to show the actual classes, member data, member functions, access specifiers (`public`, `private`, and `protected`), and inheritance relationships where applicable. 

8. Conclusion
This part of the report focuses on implementing the Data Processing module and preparing it for testing and integration. The proposed functions provide essential numerical data-processing operations that support the wider Data Visualization Library. The application of object-oriented programming principles also contributes to a modular, reusable, and maintainable design. Compilation, testing, and integration will establish whether the implementation meets the project requirements.