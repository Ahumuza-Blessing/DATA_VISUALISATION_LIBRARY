#include "DataLoader.hpp"

#include <fstream>
#include <string>
#include <utility>
#include <vector>

namespace
{
    // Parse one CSV line into individual fields.
    bool parseCSVLine(
        const std::string& line,
        std::vector<std::string>& fields)
    {
        fields.clear();

        std::string field;
        bool insideQuotes = false;
        bool quoteClosed = false;

        for (std::size_t i = 0; i < line.size(); ++i)
        {
            char ch = line[i];

            if (insideQuotes)
            {
                if (ch == '"')
                {
                    if (i + 1 < line.size() && line[i + 1] == '"')
                    {
                        field += '"';
                        ++i;
                    }
                    else
                    {
                        insideQuotes = false;
                        quoteClosed = true;
                    }
                }
                else
                {
                    field += ch;
                }
            }
            else
            {
                if (ch == ',')
                {
                    fields.push_back(field);
                    field.clear();
                    quoteClosed = false;
                }
                else if (ch == '"' && field.empty() && !quoteClosed)
                {
                    insideQuotes = true;
                }
                else if (ch == '"' || quoteClosed)
                {
                    return false;
                }
                else
                {
                    field += ch;
                }
            }
        }

        if (insideQuotes)
        {
            return false;
        }

        fields.push_back(field);
        return true;
    }
}

bool DataLoader::loadCSV(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        return false;
    }

    std::vector<std::string> newHeaders;
    std::vector<std::vector<std::string>> newRows;
    std::string line;

    // The first line contains the column headers.
    if (!std::getline(file, line))
    {
        return false;
    }

    // Handle Windows-style line endings.
    if (!line.empty() && line.back() == '\r')
    {
        line.pop_back();
    }

    if (!parseCSVLine(line, newHeaders) || newHeaders.empty())
    {
        return false;
    }

    // Reject empty column names.
    for (const std::string& header : newHeaders)
    {
        if (header.empty())
        {
            return false;
        }
    }

    // Read and validate the remaining data rows.
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        std::vector<std::string> fields;

        if (!parseCSVLine(line, fields))
        {
            return false;
        }

        // Every row must have the same number of fields as the header.
        if (fields.size() != newHeaders.size())
        {
            return false;
        }

        newRows.push_back(std::move(fields));
    }

    // Detect a file-reading error.
    if (file.bad())
    {
        return false;
    }

    // Replace existing data only after successful loading.
    headers = std::move(newHeaders);
    rows = std::move(newRows);

    return true;
}

const std::vector<std::string>& DataLoader::getHeaders() const
{
    return headers;
}

const std::vector<std::vector<std::string>>& DataLoader::getRows() const
{
    return rows;
}

std::size_t DataLoader::getRowCount() const
{
    return rows.size();
}