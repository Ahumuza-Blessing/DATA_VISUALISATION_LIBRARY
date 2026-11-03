#include "ImageExporter.hpp"
#include <cassert>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
int main() {
    const std::string path = "test_exporter.svg";
    const std::string svg = "<svg><text>Hello</text></svg>";
    ImageExporter::saveSVG(svg, path);
    const auto savedPath = ImageExporter::outputFile(path);
    assert(std::filesystem::path(savedPath).parent_path().filename() == "output");
    std::ifstream input(savedPath);
    assert(input.good());
    std::string saved((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    assert(saved == svg);
    input.close();
    std::remove(savedPath.c_str());
    std::cout << "ImageExporter tests passed.\n";
}
