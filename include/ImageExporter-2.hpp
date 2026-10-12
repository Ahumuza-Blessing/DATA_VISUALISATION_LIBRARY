#ifndef IMAGE_EXPORTER_HPP
#define IMAGE_EXPORTER_HPP

#include <string>
#include <vector>

/**
 * @brief Declares the interface for exporting rendered image data.
 *
 * Phase 1: This header defines the proposed public interface only.
 * The function implementation and image-format writing logic belong
 * in ImageExporter.cpp during Phase 2.
 *
 * Design note:
 * The group must confirm the image representation and supported format
 * before this interface is finalized.
 */
class ImageExporter {
public:
    /**
     * @brief Construct an ImageExporter.
     */
    ImageExporter() = default;

    /**
     * @brief Export raw RGB pixel data to a file.
     *
     * @param filename Destination file path.
     * @param width Image width in pixels.
     * @param height Image height in pixels.
     * @param rgbData Pixel bytes in RGB order: red, green, blue,
     *                repeated for each pixel from left to right,
     *                top to bottom.
     *
     * @return true if export succeeds; false if validation or writing fails.
     *
     * Important:
     * This is a proposed interface. The team must decide which image
     * format will be supported and implement the matching writer in Phase 2.
     */
    bool exportImage(const std::string& filename,
                     int width,
                     int height,
                     const std::vector<unsigned char>& rgbData) const;
};

#endif // IMAGE_EXPORTER_HPP
