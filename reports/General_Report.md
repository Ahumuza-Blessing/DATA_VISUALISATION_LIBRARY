
 FINAL PROJECT REPORT
Submitted by Group4
Group Members
Member		Registration No.	Assigned module
ADONGA PHILLIP	25/U/30117/PS	Data Loader
ATWINE JEANES	25/U/08700/PS	Data Processing
AHUMUZA BLESSING	25/U/08678/PS	Statistics
EGERU MICHAEL	25/U/1512	Count Plot
SERUGYA FAHAD	25/U/26725	Histogram
MUGERWA SHADRACK STEPHEN	25/U/08752/PS	KDE Plot
TWINOMUJUNI ROMEO	25/U/04735/PS	Axis
WALUGEMBE MUHAISINAH N.	25/U/08790/PS	Annotations
KISAKYE JEMIMA	25/U/08730/PS	Renderer
NAMUBIRU LOUISE	25/U/07958/PS	Image Exporter

Abstract
This project presents the design and implementation of a reusable data visualization library in C++17. The library is designed to load tabular data from CSV files, prepare data for analysis, calculate descriptive statistics, and create three plot types: Count Plots, Histograms, and Kernel Density Estimation (KDE) Plots. The system uses a modular architecture comprising Data Loader, Data Processor, Statistics, Count Plot, Histogram, KDEPlot, Axis, Annotation, Renderer, and Image Exporter components. Plot output is generated as Scalable Vector Graphics (SVG) without relying on a third-party plotting or graphics framework. CMake is used to build, compile the library and example programs, to ensure the program runs.
The repository includes examples for each plot type and an integrated example, as well as ten registered tests. This report describes the problem, objectives, related concepts, requirements, architecture, implementation and testing approach. 
Introduction
Our project, data visualization represents information through graphical forms using different modules; Count Plot helps compare the frequency of categories, a histogram groups numerical observations into intervals; and a Kernel Density Estimation plot provides a smooth estimate of a numerical distribution. These representations help users inspect the structure of data, but their usefulness depends on correct calculations, clear labels, suitable scales, and faithful rendering.
The project applies C++17 to the development of a small reusable data visualization library. Instead of depending on a third-party graphics framework, the project calculates plot data and generates SVG markup using C++ components. Our repository separates data loading, preparation, statistics, plot calculations, axes, annotations, rendering, and export into distinct modules, The program uses the CMake to build, compile the library and example programs to ensure the successful running of the project
 Problem addressed by the project;
A programmer who wants to visualize a dataset may need to implement data preparation, statistical calculations, chart geometry, axis scaling, labels, rendering, and file output. Repeating these responsibilities in each application increases duplicated code and makes maintenance harder. The project addresses this learning and software-design problem by packaging selected visualization functions into reusable C++ modules with a shared rendering and export pipeline

OBJECTIVES
Main Objective:
To design and implement a modular C++17 library that reads and prepares tabular data, calculates descriptive statistics, generates selected statistical plots, and exports those plots as SVG files.
 Other Objectives;
•	Implement a CSV data-loading component for reading tabular input.
•	Prepare loaded data by trimming text, removing blank rows, selecting columns, and converting numerical text where required.
•	Calculate descriptive statistics including count, mean, median, minimum, maximum, variance, and standard deviation.
•	Generate categorical Count Plots, numerical Histograms, and KDE Plots.
•	Provide shared axis scaling and tick generation, plus support for positioned annotations.
•	Render plots as SVG and save the output through an image-export component.
•	Organize the project into reusable modules, example programs, and separately registered tests using CMake.
.
 Background and Related Concepts
Data Visualization
Data visualization maps information to visual marks such as positions, lengths, lines, and labels. The choice of visual form should reflect the analytical question. Frequency charts are useful for categorical comparisons, while distribution charts show how numerical observations are spread. A graph should include enough context—such as a title, axis labels, and meaningful scales—for a reader to interpret it without guessing.
CSV Data and Data Preparation
CSV is a common text format for tabular data. A data loader reads the file into a representation of rows and columns, while a data-processing component prepares the values for downstream calculations. Typical preparation tasks include trimming whitespace, handling blank rows, selecting a column, and converting numeric text into numeric values.
 Descriptive Statistics
Descriptive statistics summarize adataset. Count reports the number of observations. Mean is the arithmetic average. Median is the middle value after sorting, or the average of the two middle values when the sample size is even. Minimum and maximum identify the observed range. Variance measures dispersion around the mean, and standard deviation is the square root of variance. 
 Count Plot
A Count Plot represents the number of observations belonging to each category. The calculation groups equal categorical values and counts their occurrences. The rendered plot can then display categories and their counts so that a user can compare frequencies. Its correctness can be tested with a small input whose category frequencies are known in advance.

 Histogram
A Histogram summarizes numerical data by dividing a range into intervals, commonly called bins, and counting the values that fall into each interval. The number and width of bins affect the level of detail visible in the plot. Testing checks bin boundaries, the treatment of the maximum value, empty bins, and the relationship between the total bin counts and the number of valid observations.
 Kernel Density Estimation Plot
Kernel Density Estimation (KDE) estimates a smooth probability density from numerical observations. The repository describes its KDE component as using a Gaussian kernel. Conceptually, each observation contributes a smooth kernel around its value, and the contributions are combined to form a curve. 
SVG as a Rendering Format
Scalable Vector Graphics is an XML-based format for describing two-dimensional vector graphics, including paths, shapes. SVG suits static plots because a viewer can scale vector elements without the pixilation typical of raster images. It is also text-based, so the renderer can construct a document by emitting SVG elements. Correctness requires well-formed markup and sensible coordinates, dimensions, labels, and graphical elements.
Modular C++ Design
A reusable library separates public interfaces from implementation details. In this project, public header files are located in include and implementation files in src. This organization lets examples and tests use the same module interfaces. The project uses encapsulation in components such as Axis and Annotation, and emphasizes separation of responsibilities.
 Build Configuration and Testing
CMake provides a way to describe targets, source files, include directories, and tests independently of a particular IDE. The project's CMakeLists.txt requires CMake 3.16, selects C++17, builds the dataviz library, links the examples to it, and registers test executables. CTest can then execute the registered tests and report their outcomes. 
 REQUIREMENTS AND DESIGN
The system loads and prepares data, calculates statistics and plot values, render chart titles, axes, labels, ticks and annotations, and saves SVG files. The design uses a pipeline: Data Loader reads CSV files; Data Processor prepares data; Statistics, Count Plot, Histogram, or KDEPlot calculates results; Axis supports scaling and ticks; Annotation stores notes; Renderer creates SVG markup; and Image Exporter writes the file. Different modules work together to make up the program:
Component Responsibility

Component	Input / role	Output / responsibility
Data Loader	CSV file path	Reads input rows and columns as text.
Data Processor	Loaded tabular data	Trims text, removes blank rows, extracts columns, and converts numeric text.
Statistics	Numerical values	Calculates count, mean, median, minimum, maximum, variance, and standard deviation.
Count Plot	Categorical values	Calculates category frequencies.
Histogram	Numerical values	Calculates bins and counts.
KDEPlot	Numerical values	Estimates density points using a Gaussian kernel.
Axis	Ranges and drawing dimensions	Maps numerical values to drawing coordinates and generates ticks.
Annotation	Positioned notes	Stores notes that can be included in a graph.
Renderer	Plot data and presentation details	Creates SVG markup, including plot elements and graph labels.
Image Exporter	SVG string and destination	Saves SVG files; creates the default output directory if needed.



System Architecture
This shows how and where ever module was used during the implementation of the program and the order in which the program runs.

 

Note: AI was used to generate the chart above.
Project Directory Structure
The repository uses a modular structure. The main folders and files documented in README.md are summarized below;
Path	Purpose
Include/	Public headers: DataLoader.hpp, DataProcessor.hpp, Statistics.hpp, CountPlot.hpp, Histogram.hpp, KDEPlot.hpp, Axis.hpp, Annotation.hpp, Renderer.hpp, ImageExporter.hpp.
src/	Matching C++ implementation files for the ten modules.
examples/	countplot_example.cpp, histogram_example.cpp, kdeplot_example.cpp, complete_library_example.cpp.
tests/	Ten test source files for data loading, processing, statistics, plots, axes, annotations, exporter, and renderer.
data/input/	Example CSV datasets including student marks, sales, and subject-related data.
data/output/	Default destination for generated SVG artifacts.
CMakeLists.txt	Configures the C++17 library target, examples, and registered tests.
README.md	Project overview, member allocations, build instructions, examples, and design notes.
reports/	Progress reports and module documentation, according to the README.

 Implementation
The implementation is written in C++17. CMake defines a library target named dataviz and compiles the ten module implementation files into that target. The examples in the shared library, allowing the examples to exercise the same public interfaces used by other client programs 
Contribution of each module in the implementation
Data Loader
Data Loader is responsible for reading a CSV file and representing its contents as rows and columns of text. Keeping file reading separate from chart calculations means that plot modules do not need to implement their own input routines. 
Data Processor
Data Processor prepares the loaded values for use by the analysis and plot modules. The project documentation identifies trimming text, removing blank rows, extracting columns, and converting numerical text as its responsibilities. These operations help downstream modules work with values in a consistent form.
Statistics
Statistics calculates basic descriptive summaries: count, mean, median, minimum, maximum, variance, and standard deviation. These measures can help describe the dataset before or alongside visualization. For example, the mean gives a measure of central tendency, while standard deviation summarizes spread. Correctness tests should cover odd and even sample sizes for median, constant datasets, negative values, and empty input where those cases are defined by the API.
Count Plot
Count Plot calculates the frequency of each categorical value. The resulting counts are passed into the shared rendering path. A suitable test dataset might contain repeated category labels such as A, B, A, C, B, A; the expected frequencies would be A = 3, B = 2, and C = 1. 
Histogram
Histogram divides numerical observations into bins and counts values in each bin. The plot module handles the statistical grouping, while the renderer handles the visual representation.
 KDEPlot
KDEPlot estimates density points using a Gaussian kernel. Compared with a histogram, which displays counts in discrete bins, KDE produces a smooth curve intended to communicate the shape of a numerical distribution. The result depends on the observations and the bandwidth used by the implementation.
Axis
Axis maps numerical data ranges to drawing coordinates and generates tick values. It is a shared support module because different plot types need consistent scaling and labelled axes. Its encapsulated range state and methods for scaling values, generating ticks, and updating ranges are described in the repository documentation. Testing covers equal minimum and maximum values, negative ranges, endpoints, and ranges that cross zero.
Annotation
Annotation stores positioned notes that can be placed on a plot. Its role is distinct from the renderer's title and axis-label work: the repository explicitly notes that Annotation stores additional notes, while Renderer adds the plot title and axis labels. Keeping annotation data separate from drawing code allows the renderer to position and draw notes consistently.
 Renderer
Renderer produces SVG markup for the three plot types. It combines plot-specific values with graph presentation features such as titles, axes, scales, labels, tick marks, and optional annotations. A shared renderer avoids repeating drawing code in every plot module. 
Image Exporter
Image Exporter saves the rendered SVG content as a file. By default, the output directory is data/output/, and the repository documentation states that the directory is created if it does not exist. The documented example Image Exporter::saveSVG (svg, "mygraph.svg") writes to data/output/mygraph.svg; when an explicit output path is supplied, the exporter uses that path. 
 Build Configuration
CMakeLists.txt sets the project version to 1.0, requires C++17, builds the dataviz library from the ten module source files, exposes include/ as a public include directory, and defines the default output directory. It creates four example executables and registers ten tests using a helper function. The build configuration includes compiler-specific options to keep assertions enabled for test targets 
 



Running the Project
From the repository root, configure and build the project with a C++17-compatible compiler and CMake 3.16 or newer. The following commands are used:
cmake -S . -B build -G "MinGW Makefiles"
 cmake --build build
 ctest --test-dir build --output-on-failure
Get-ChildItem .\build\*_example.exe | ForEach-Object {
  Write-Host "Running $($_.Name)"
& $_.FullName
  if ($LASTEXITCODE -ne 0) { throw "$($_.Name) failed" }
}
Testing and Results
Testing checks whether the implementation behaves as expected and helps reveal defects at module boundaries. The repository contains ten CMake-registered test executables covering data loading, data processing, statistics, Count Plot, Histogram, KDEPlot, Axis, Annotation, Image Exporter, and Renderer. The program was tested and it successfully performed as expected.
Insert graphs
Strengths of the project
•	Clear separation between input handling, preparation, statistics, plotting, rendering, and export.
•	One shared renderer is used by the plot types, reducing duplicated drawing logic.
•	The library uses SVG and does not require a third-party plotting framework according to the project documentation.
•	Public headers, implementation files, examples, and tests are organized into distinct directories.
•	CMake provides a common build configuration and registers module tests.
•	Responsibilities are allocated across the group, making the project suitable for collaborative development and review.
 Challenges and Lessons Learned
Limitations
•	The library currently documents three plot types; other visualization types are outside the stated scope.
•	The output described by the project is SVG, not an interactive chart or dashboard.
•	The precise CSV edge-case behavior should be documented from the parser implementation.
•	The KDE bandwidth and variance convention should be made explicit in technical documentation.
•	Test outcomes depend on the actual compiler and operating system and should be recorded rather than assumed.
•	The project documentation states that no inheritance hierarchy or virtual functions are used; future designs could evaluate whether polymorphism is useful, but it is not required for the current architecture.
Future Improvements
             Although the C++ Data Visualization Library achieves its intended objectives, several improvements can be made to enhance its functionality, efficiency, and usability in the future.
The proposed improvements include:
•	 Extend the library to support more visualization types, such as pie charts, histograms, scatter plots, and other statistical graphs.
•	Improve the data processing module by introducing additional data-cleaning operations, missing-value handling, data validation, and support for larger datasets
•	Performance Optimization: Improve the efficiency of the library when processing and visualizing large volumes of data.
•	Comprehensive Testing and Documentation: Introduce more extensive unit and integration tests and provide detailed documentation to make the library easier to understand, maintain, and use.
Conclusion
The Group 4 project designed and organized a reusable C++17 data visualization library for CSV-based data preparation, descriptive statistics, and three plot types: Count Plot, Histogram, and KDE Plot. Its modules divide responsibilities among data loading, data processing, statistical calculations, plot calculations, axis mapping, annotations, SVG rendering, and image exporting. CMake provides a library target, four example programs, and ten registered module tests. The use of a shared SVG renderer and a separate exporter illustrates how a small visualization library can be structured for reuse and maintainability.
Development of the C++ Data Visualization Library provided an opportunity to apply C++ programming concepts learnt in our programming class in developing a practical and reusable software solution.The project brought together different modules responsible for data processing, visualization, rendering, and other supporting functionalities to simplify the transformation of raw data into meaningful visual representations. We also gained practical experience in collaborative software development and version control using GitHub.
Despite the challenges encountered during development, the project achieved its main purpose of demonstrating how C++ can be used to develop structured and reusable tools for data processing and visualization. It also strengthened our practical programming, problem-solving, teamwork, and software development skills. Overall, the project executed successfully as expected after several trials by the cooperation and activeness of all group members.
References
1.	International Organization for Standardization. (2024). Programming languages — C++ (ISO/IEC 14882:2024). https://www.iso.org/standard/83626.html

2.	Stroustrup, B. (2014). Programming: Principles and practice using C++ (2nd ed.). Addison-Wesley.

3.	World Wide Web Consortium. (2026). Scalable Vector Graphics (SVG) 2. https://www.w3.org/TR/SVG2/
4.	https://lms.marconilab.org/login?callbackUrl=https%3A%2F%2Flms.marconilab.org%2F
5.	 Kitware, Inc. (n.d.). Testing and CTest. CMake Documentation. https://cmake.org/cmake/help/latest/guide/tutorial/Testing%20and%20CTest.html
6.	In addition some AI tools(chat gpt, claude, Gemini, Google and many others) were used to assist in the successful implementation of our project 




