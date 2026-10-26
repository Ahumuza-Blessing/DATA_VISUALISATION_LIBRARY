
#include "ImageExporter.hpp"

#include <cassert>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

int main() {
    // Test 1: Save SVG content to a file.
        const std::string outputPath =
                "image_exporter_test_output.svg";

                    const std::string svg =
                            "<svg xmlns=\"http://www.w3.org/2000/svg\">"
                                    "<text>ImageExporter test</text>"
                                            "</svg>";

                                                ImageExporter::saveSVG(svg, outputPath);

                                                    // Test that the file was created and can be opened.
                                                        std::ifstream input(outputPath);
                                                            assert(input.is_open());

                                                                // Read the saved file.
                                                                    const std::string saved(
                                                                            (std::istreambuf_iterator<char>(input)),
                                                                                    std::istreambuf_iterator<char>()
                                                                                        );

                                                                                            input.close();

                                                                                                // Check that the saved content is correct.
                                                                                                    assert(saved == svg);

                                                                                                        // Remove the temporary output file.
                                                                                                            std::remove(outputPath.c_str());

                                                                                                                // Test 2: Check error handling for an invalid path.
                                                                                                                    bool exceptionThrown = false;

                                                                                                                        try {
                                                                                                                                ImageExporter::saveSVG(
                                                                                                                                            svg,
                                                                                                                                                        "image_exporter_missing_directory_7f39/output.svg"
                                                                                                                                                                );
                                                                                                                                                                    } catch (const std::runtime_error&) {
                                                                                                                                                                            exceptionThrown = true;
                                                                                                                                                                                }

                                                                                                                                                                                    assert(exceptionThrown);

                                                                                                                                                                                        return 0;
                                                                                                                                                                                        }
                                                                                                                                                                                        