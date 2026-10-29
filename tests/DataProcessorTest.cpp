#include "DataProcessor.hpp"
#include <cassert>
#include <iostream>

#include <stdexcept>

int main() {
    assert(DataProcessor::trim("  hello \t") == "hello");
    DataProcessor::Table raw{{"heading", "score"}, {" A ", " 10 "}, {" ", " "}};
    auto clean = DataProcessor::cleanRows(raw);
    assert(clean.size() == 2);
    assert(clean[1][0] == "A");
    auto column = DataProcessor::getColumn(clean, 1);
    assert(column.size() == 1 && column[0] == "10");
    auto values = DataProcessor::toNumeric({" 10 ", "bad", "20"});
    assert(values.size() == 2 && values[1] == 20.0);
    bool threw = false;
    try { DataProcessor::toNumeric({"bad"}, false); }
    catch (const std::invalid_argument&) { threw = true; }
    assert(threw);
    std::cout << "DataProcessor tests passed.\n";
}