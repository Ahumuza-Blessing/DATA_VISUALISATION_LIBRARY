#include "ImageExporter.hpp" // Includes the ImageExporter class declarations

#include <filesystem> // Provides functions for handling file paths and directories
#include <fstream>    // Provides std::ofstream for writing SVG files
#include <stdexcept>  // Provides exceptions for reporting errors

// Determines the full destination path where an SVG file should be saved.
std::string ImageExporter::outputFile(const std::string& filename) {

    // Checks whether the supplied filename is empty.
    if (filename.empty()) {
        // Throws an exception because a file cannot be saved without a filename.
        throw std::invalid_argument("Output filename cannot be empty.");
    }

    // Converts the filename string into a filesystem path object.
    // This makes it easier to inspect and combine directory paths.
    std::filesystem::path destination(filename);

    // If only a filename is given, I want it inside data/output.
    // Absolute and explicitly named directory paths still work normally.

    // is_absolute() checks whether the path starts from a filesystem root.
    // has_parent_path() checks whether the filename already includes a directory.
    // Both conditions must be true for the default output directory to be added.
    if (!destination.is_absolute() && !destination.has_parent_path()) {

        // Checks whether the build system defined a custom output directory.
        // #ifdef is a preprocessor directive evaluated before compilation.
        #ifdef DATAVIZ_DEFAULT_OUTPUT_DIR

        // Uses the output directory configured by the build system.
        // The / operator joins filesystem path components.
        destination = std::filesystem::path(DATAVIZ_DEFAULT_OUTPUT_DIR) / destination;

        #else // Executes during preprocessing if the macro was not defined

        // Uses data/output as the default destination directory.
        destination = std::filesystem::path("data") / "output" / destination;

        #endif // Ends the conditional compilation block
    }

    // Converts the filesystem path back into a string and returns it.
    return destination.string();
}

// Writing the SVG to a file is the final step after rendering.
void ImageExporter::saveSVG(
    const std::string& svg,      // SVG markup to be written to the file
    const std::string& filePath  // Requested destination filename or path
) {
    // Calls outputFile() to determine the actual destination.
    // const prevents the destination from being changed afterward.
    const std::filesystem::path destination(outputFile(filePath));

    // The output directory might not exist on another person's computer.
    // Checks whether the destination includes a parent directory.
    if (destination.has_parent_path()) {

        // Creates the required directories if they do not already exist.
        // parent_path() returns the directory containing the destination file.
        // create_directories() can create multiple missing directory levels.
        std::filesystem::create_directories(destination.parent_path());
    }

    // Opens the destination file for writing.
    // std::ofstream creates the file if it does not already exist.
    // By default, opening an existing file this way replaces its contents.
    std::ofstream file(destination);

    // Checks whether the output file was opened successfully.
    if (!file.is_open()) {

        // Throws an exception containing the destination path.
        throw std::runtime_error("Could not create output file: " + destination.string());
    }

    // Writes the SVG markup into the output file.
    // The << operator sends the string into the file stream.
    file << svg;

    // Checks whether the file stream reports an error after writing.
    if (!file.good()) {

        // Throws an exception if writing the SVG content failed.
        throw std::runtime_error("Failed while writing output file: " + destination.string());
    }

    // The file stream is automatically closed when it goes out of scope.
}
