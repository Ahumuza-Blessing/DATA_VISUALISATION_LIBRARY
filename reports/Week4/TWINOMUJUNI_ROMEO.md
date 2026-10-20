# INDIVIDUAL WEEKLY PROGRESS REPORT

**Project:** C++ Data Visualization Library  
**Name:** TWINOMUJUNI ROMEO  
**Module:** Axis

## 1. Objectives

1. Complete the implementation of the Axis class functions.
2. Apply object-oriented programming principles to the module.
3. Implement numerical scaling and tick generation.
4. Review the class structure and prepare it for integration with other modules.

## 2. Activities Carried Out

1. Implemented the Axis constructor to initialize the data and screen ranges.
2. Developed the `scale()` function to convert numerical values into graph positions.
3. Implemented the `ticks()` function to generate evenly spaced axis values.
4. Added getter and setter functions for accessing and updating axis ranges.
5. Added validation to prevent division by zero when minimum and maximum values are equal.
6. Submitted the Axis implementation through a pull request, which was merged into the main project.

## 3. Object-Oriented Programming Concepts

### A. Encapsulation

Encapsulation was implemented by declaring the Axis data members as private.

These members store the minimum and maximum data values and the starting and ending screen positions.

They cannot be accessed directly from outside the class. Instead, public getter and setter functions provide controlled access to the stored values.

For example, `setRange()` allows the data range to be changed while checking that the minimum and maximum values are not equal.

### B. Inheritance

Inheritance has not yet been implemented in the Axis module.

The Axis class currently operates independently and does not inherit from another class.

### C. Polymorphism

Polymorphism has not yet been implemented in the Axis module.

The class currently uses its own functions without function overriding or virtual methods.

## 4. Class Layout

The Axis class contains private data members and public member functions.

The class diagram will be drawn separately on paper, showing the constructor, scaling function, getter and setter functions, and their access specifiers.

There are currently no protected members or inheritance relationships.

![alt text](image-1.png)
## 5. Challenges Experienced

1. Understanding how to convert data values into drawing positions.
2. Handling invalid ranges that could result in division by zero.
3. Maintaining consistency between the header file and implementation file.
4. Preparing the class for use by other plotting modules.

## 6. Work for the Next Week

1. Test scaling and tick generation using different numerical ranges.
2. Review the implementation of the Axis class against the header declarations.
3. Integrate the Axis module with the Renderer and other plotting modules.
4. Review how additional OOP concepts could be introduced where appropriate.

## 7. AI Use

AI was used to review code logic and advise accordingly.