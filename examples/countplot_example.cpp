#ifndef COUNTPLOT_HPP // Checks whether this header has already been included
#define COUNTPLOT_HPP // Defines the header guard to prevent repeated inclusion

#include <cstddef> // Provides std::size_t, used for storing category counts
#include <map>     // Provides std::map, which stores data as key-value pairs
#include <string>  // Provides std::string for storing category names
#include <vector>  // Provides std::vector for storing a list of categories

// The CountPlot class counts how many times each category appears.
// For example, A, B, A, C, A gives A=3, B=1, C=1.
// The Renderer can use these counts to draw the bars of a count plot.
class CountPlot {

public: // Makes the following declarations accessible outside the class

    // 'using' creates a shorter name for a longer data type.
    // Counts is another name for std::map<std::string, std::size_t>.
    //
    // std::string represents the category name, such as "Computer Science".
    // std::size_t represents how many times that category appears.
    //
    // Example:
    // "Computer Science" -> 5
    // "Information Technology" -> 3
    //
    // A map also keeps its keys sorted alphabetically by default.
    using Counts = std::map<std::string, std::size_t>;

    // Declares a function that counts occurrences of each category.
    //
    // static means we can call the function using the class name,
    // without creating a CountPlot object.
    //
    // const means the function cannot modify the input vector.
    // & means the vector is passed by reference, avoiding a full copy.
    //
    // The function returns a Counts map containing the results.
    static Counts calculate(const std::vector<std::string>& categories);
};

#endif // Ends the header guard
