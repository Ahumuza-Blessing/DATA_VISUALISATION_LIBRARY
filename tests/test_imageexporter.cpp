#include "ImageExporter.hpp" // Includes the ImageExporter functions being tested
#include <cassert>           // Provides assert() for checking test conditions
#include <cstdio>            // Provides std::remove() for deleting the test file
#include <filesystem>        // Provides filesystem path operations
#include <fstream>           // Provides std::ifstream for reading the saved file
#include <iostream>          // Provides std::cout for displaying test results
#include <iterator>          // Provides std::istreambuf_iterator for reading file contents
#include <string>            // Provides std::string for storing text and paths

int main() { // Entry point of the ImageExporter test program

    // Defines the filename that will be used during the test.
    // const prevents the filename from being modified.
    const std::string path = "test_exporter.svg";

    // Creates a simple SVG string containing a text element.
    // This is sample SVG markup used to test file saving.
    const std::string svg = "<svg><text>Hello</text></svg>";

    // Calls ImageExporter to save the SVG string to a file.
    ImageExporter::saveSVG(svg, path);

    // Retrieves the actual path where the SVG file was saved.
    // auto lets the compiler determine the return type.
    const auto savedPath = ImageExporter::outputFile(path);

    // Checks that the immediate parent directory is named "output".
    // parent_path() retrieves the containing directory.
    // filename() retrieves the last component of that directory path.
    assert(std::filesystem::path(savedPath).parent_path().filename() == "output");

    // Opens the saved SVG file for reading.
    std::ifstream input(savedPath);

    // Verifies that the input stream is in a good state.
    // This helps confirm that the saved file was opened successfully.
    assert(input.good());

    // Reads the entire saved file into a string.
    // istreambuf_iterator<char> reads characters from the file stream.
    // The default-constructed iterator represents the end of the stream.
    std::string saved((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

    // Verifies that the saved file contents exactly match the original SVG.
    assert(saved == svg);

    // Closes the input file after reading its contents.
    input.close();

    // Deletes the temporary SVG file created during testing.
    // c_str() converts the C++ string into a C-style string.
    std::remove(savedPath.c_str());

    // Displays a success message if all enabled assertions pass.
    std::cout << "ImageExporter tests passed.\n";
}
