#ifndef IMAGEEXPORTER_HPP
#define IMAGEEXPORTER_HPP

#include <string>

class ImageExporter {
public:
    static void saveSVG(const std::string& svg, const std::string& filePath);
};

#endif