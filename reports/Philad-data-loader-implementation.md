Phase 2 Report: DataLoader Implementation and OOP

1. Introduction

Phase 2 focused on implementing the DataLoader module of the Data Visualization Library using C++. The purpose of this module is to read CSV files and make their contents available to other components of the library.

The implementation applies object-oriented programming principles, particularly classes, encapsulation, and access control.

2. Class Used

The main class developed in this module is "DataLoader". It is declared in "include/DataLoader.hpp" and implemented in "src/DataLoader.cpp".

The class combines the data required to store CSV contents with the functions used to load and retrieve that data. This makes the loading functionality reusable and keeps file-reading operations organized within one component.

3. Data Members

The class has two private data members:

- "headers": a "std::vector<std::string>" that stores the column names from the CSV header.
- "rows": a "std::vector<std::vector<std::string>>" that stores the data records, with each field represented as a string.

Storing values as strings allows later processing modules to decide how to interpret or convert the data.

4. Member Functions

The class exposes four public functions:

- "loadCSV(const std::string& filename)": opens a CSV file, reads its contents, validates the data, and returns a Boolean result indicating success or failure.
- "getHeaders() const": provides read-only access to the column names.
- "getRows() const": provides read-only access to the loaded records.
- "getRowCount() const": returns the number of data records, excluding the header.

5. Access Specifiers and Encapsulation

The "headers" and "rows" members are private. This prevents ordinary external code from directly accessing or modifying the class's internal data.

The four member functions are public, allowing other components to use the class through a controlled interface.

The class has no protected members. A protected member would be accessible to derived classes, but the current implementation does not use inheritance.

Encapsulation is demonstrated by keeping the data private and providing public functions to operate on or inspect it. The loader also uses temporary storage while validating new data, replacing the existing data only after successful loading.

6. Inheritance and Polymorphism

The current DataLoader implementation does not use inheritance or polymorphism. It is a standalone class because its current responsibilities do not require derived classes or multiple interchangeable implementations.

Polymorphism could be introduced in a future design if the library needs a common interface for different data-loading formats.

7. CSV Parsing and Validation

The implementation supports ordinary comma-separated fields, quoted fields containing commas, and escaped double quotes.

It checks that each data row contains the same number of fields as the header. It also handles missing files, empty files, and malformed rows by reporting failure.

The current parser is intended for single-line CSV records. Quoted fields spanning multiple lines are not supported.

8. Testing and Results

The implementation was compiled using GCC 15.2.0 with the C++17 standard and compiler warning options enabled.

The tests covered:

- Loading a CSV file containing column headers and data records.
- Reading quoted fields containing commas.
- Reading escaped double quotes.
- Counting the number of data records.
- Rejecting a missing file.
- Rejecting a row with an incorrect number of fields.
- Preserving previously loaded data after a failed load.

The basic CSV and error-handling tests passed after the invalid-row test case was corrected.

9. How the Class Is Used

The test program creates a "DataLoader" object, calls "loadCSV()" with a filename, and checks whether loading succeeds. It then uses "getHeaders()", "getRows()", and "getRowCount()" to access the loaded information.

This interface allows other library modules to use the data without needing to know the internal details of CSV parsing.

10. Conclusion

Phase 2 established the core CSV-loading functionality of the DataLoader module. The implementation provides a reusable interface for loading data, retrieving column names and records, and checking the number of data rows.

Compilation and functional testing demonstrated the expected behaviour for the cases tested. The next phase will focus on additional edge cases, integration with the rest of the library, and further testing.