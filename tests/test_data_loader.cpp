#include "DataLoader.hpp"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
int main() {
    const char* path = "test_dataloader.csv";
    { std::ofstream out(path); out << "name,score,\nA,7,\n"; }
    auto rows = DataLoader::loadCSV(path);
    assert(rows.size() == 2);
    assert(rows[0].size() == 3);
    assert(rows[1][0] == "A");
    assert(rows[1][2].empty());
    std::remove(path);
    bool threw = false;
    try { DataLoader::loadCSV("no_such_csv_file_763929.csv"); }
    catch (const std::runtime_error&) { threw = true; }
    assert(threw);
    std::cout << "DataLoader tests passed.\n";
}
