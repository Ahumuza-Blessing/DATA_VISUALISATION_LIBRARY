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
    bool loadCSV(const std::string& filename);

    const std::vector<std::string>& getHeaders() const;
    const std::vector<std::vector<std::string>>& getRows() const;

    std::size_t getRowCount() const;
};

#endif