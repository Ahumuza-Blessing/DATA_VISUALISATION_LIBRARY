#include "DataLoader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    bool writeFile(
        const std::filesystem::path& filename,
        const std::string& contents)
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            return false;
        }

        file << contents;
        return file.good();
    }
}

int main()
{
    namespace fs = std::filesystem;

    const fs::path testDirectory = "test_data";

    if (!fs::create_directories(testDirectory) &&
        !fs::is_directory(testDirectory))
    {
        std::cerr << "Test failed: Could not create test directory.\n";
        return 1;
    }

    const fs::path sampleFile = testDirectory / "sample.csv";
    const fs::path invalidFile = testDirectory / "invalid.csv";
    const fs::path missingFile = testDirectory / "missing.csv";

    if (!writeFile(
            sampleFile,
            "Name,Age,Description\n"
            "John,20,\"Student, first year\"\n"
            "Mary,21,\"She said \"\"hello\"\"\"\n"
            "Peter,22,Engineer\n"))
    {
        std::cerr << "Test failed: Could not create sample CSV.\n";
        return 1;
    }

    if (!writeFile(
            invalidFile,
            "Name,Age\n"
            "John,20\n"
            "Mary\n"))
    {
        std::cerr << "Test failed: Could not create invalid CSV.\n";
        return 1;
    }

    DataLoader loader;

    // Test successful loading.
    if (!loader.loadCSV(sampleFile.string()))
    {
        std::cerr << "Test failed: Could not load valid CSV.\n";
        return 1;
    }

    const auto& headers = loader.getHeaders();
    const auto& rows = loader.getRows();

    if (headers.size() != 3 ||
        headers[0] != "Name" ||
        headers[1] != "Age" ||
        headers[2] != "Description")
    {
        std::cerr << "Test failed: Incorrect headers.\n";
        return 1;
    }

    if (loader.getRowCount() != 3 || rows.size() != 3)
    {
        std::cerr << "Test failed: Expected 3 data rows.\n";
        return 1;
    }

    // Test a comma inside a quoted field.
    if (rows[0][2] != "Student, first year")
    {
        std::cerr << "Test failed: Quoted comma was parsed incorrectly.\n";
        return 1;
    }

    // Test escaped double quotes.
    if (rows[1][2] != "She said \"hello\"")
    {
        std::cerr << "Test failed: Escaped quotes were parsed incorrectly.\n";
        return 1;
    }

    std::cout << "Basic CSV tests passed.\n";

    // Test a missing file.
    if (loader.loadCSV(missingFile.string()))
    {
        std::cerr << "Test failed: Missing file was accepted.\n";
        return 1;
    }

    // Test an invalid row with too few fields.
    if (loader.loadCSV(invalidFile.string()))
    {
        std::cerr << "Test failed: Invalid row was accepted.\n";
        return 1;
    }

    // Ensure failed loads preserve previously loaded data.
    if (loader.getRowCount() != 3 ||
        loader.getHeaders().size() != 3 ||
        loader.getRows()[0][0] != "John")
    {
        std::cerr << "Test failed: Previous data was changed.\n";
        return 1;
    }

    std::cout << "Error-handling tests passed.\n";

    // Test an empty file.
    const fs::path emptyFile = testDirectory / "empty.csv";

    if (!writeFile(emptyFile, ""))
    {
        std::cerr << "Test failed: Could not create empty CSV.\n";
        return 1;
    }

    if (loader.loadCSV(emptyFile.string()))
    {
        std::cerr << "Test failed: Empty file was accepted.\n";
        return 1;
    }

    std::cout << "Empty-file test passed.\n";

    // Remove temporary test files.
    std::error_code cleanupError;
    fs::remove_all(testDirectory, cleanupError);

    if (cleanupError)
    {
        std::cerr << "Warning: Could not remove temporary test files.\n";
    }

    std::cout << "All DataLoader tests passed.\n";
    return 0;
}