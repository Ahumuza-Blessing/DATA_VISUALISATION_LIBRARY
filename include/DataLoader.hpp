#ifndef DATA_LOADER_HPP
#define DATA_LOADER_HPP

#include <cstddef>
#include <string>
#include <vector>

class DataLoader
{
private:
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> rows;

public:
    // Load a CSV file. Returns false if loading fails.
    bool loadCSV(const std::string& filename);

    // Read the column names.
    const std::vector<std::string>& getHeaders() const;

    // Read all data rows.
    const std::vector<std::vector<std::string>>& getRows() const;

    // Get the number of data rows, excluding the header.
    std::size_t getRowCount() const;
};

#endif