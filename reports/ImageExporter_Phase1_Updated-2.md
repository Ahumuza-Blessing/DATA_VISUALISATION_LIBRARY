# Image Exporter Module — Phase 1 Progress Report

**Name:** Namubiru Louise  
**Project:** Data Visualization Library in C++  
**Module:** Image Exporter  
**Reporting period:** Week 1  
**Phase:** Phase 1 — Planning and Interface Design

## 1. Objective

The objective of Phase 1 is to plan the Image Exporter module and design its public interface before implementing the file-writing functionality in Phase 2.

## 2. Module Overview

The Image Exporter module is intended to save a rendered visualization to an image file. It is responsible for handling the export request and reporting whether the export succeeds or fails. It is not responsible for creating the plot itself; that work belongs to the plotting or rendering part of the library.

The exact image format and the way rendered image data will be supplied must be agreed on by the group before implementation.

## 3. Planned Responsibilities

The module is expected to:

- Accept a destination filename.
- Receive image data from the rendering part of the library.
- Check basic input information before attempting an export.
- Write the image data in the agreed supported format.
- Report success or failure to the calling code.
- Work with the rest of the Data Visualization Library.

These responsibilities are provisional until the group confirms the rendering interface and the image format.

## 4. Phase 1 Interface Design: `ImageExporter.hpp`

As part of Phase 1, a proposed header file named `include/ImageExporter.hpp` has been designed. The header declares the public interface of the Image Exporter class. It does not contain the actual image-writing implementation.

The proposed interface uses the following method:

```cpp
bool exportImage(const std::string& filename,
                 int width,
                 int height,
                 const std::vector<unsigned char>& rgbData) const;
```

The method is designed to receive:

- `filename`: the path and name of the output image file.
- `width`: the image width in pixels.
- `height`: the image height in pixels.
- `rgbData`: the image's raw pixel bytes, arranged in RGB order.

The method returns `true` if the export succeeds and `false` if validation or writing fails. The actual function definition and file-writing logic will be implemented in `src/ImageExporter.cpp` during Phase 2.

**Design note:** This is a proposed interface, not a confirmed final interface. It assumes that the renderer can provide raw RGB pixel data. The group must confirm that assumption, the supported image format, and how errors should be handled before the interface is finalized. If the project uses a different image representation or an existing image-writing library, the header may need to be adjusted.

## 5. Proposed File Structure

The module is expected to use the following files:

- `include/ImageExporter.hpp` — public class and method declarations; designed during Phase 1.
- `src/ImageExporter.cpp` — method implementation and image-writing logic; planned for Phase 2.
- `tests/test_image_exporter.cpp` — tests for input validation and export behavior; planned for Phase 3.
- `examples/` — an example demonstrating image export, if required by the group.

The final paths should follow the repository's existing structure and the group's conventions.

## 6. Planned Workflow

1. Review the group's project requirements and existing repository structure.
2. Agree on the input image representation and supported image format.
3. Confirm the method signature and error-reporting approach with the group.
4. Finalize `include/ImageExporter.hpp`.
5. Implement the method in `src/ImageExporter.cpp` during Phase 2.
6. Test valid and invalid export requests and integrate the module during Phase 3.

## 7. Progress During This Reporting Period

The Phase 1 work described in this report focuses on planning the module's responsibilities and preparing a proposed public interface in `ImageExporter.hpp`. The implementation of the export method has not been described as completed in this report; it is planned for Phase 2.

Before submission, update this section so that it accurately reflects what has actually been completed in the repository—for example, whether the header has been uploaded to the branch, reviewed by the group, or revised after discussion.

## 8. Design Questions and Challenges

The following points still require confirmation:

- Which image format will the library support?
- Will the rendering module provide raw RGB bytes, a different pixel format, or an image object?
- Will the project use a third-party image-writing library or a custom writer?
- What error-reporting approach should be used?
- How will the exporter connect to the rendering module and the build system?

Resolving these questions early will help avoid interface changes during implementation.

## 9. Next Steps

- Discuss the proposed interface with the group.
- Confirm the image representation and file format.
- Make any required changes to `ImageExporter.hpp`.
- Begin implementing `ImageExporter.cpp` in Phase 2 once the interface is agreed upon.

## 10. Conclusion

Phase 1 establishes the proposed responsibilities and public interface of the Image Exporter module. The `ImageExporter.hpp` header is part of the planning and interface-design work, while the actual export logic is reserved for Phase 2 and testing and integration for Phase 3. The interface remains provisional until it is checked against the group's agreed design.
