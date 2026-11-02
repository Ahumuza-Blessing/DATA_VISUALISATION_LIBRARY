KDEPlot Test Suite Report
Author: MUGERWA SHADRACK STEPHEN 
Subject: Review of the unit test program for the KDEPlot kernel density estimation class
1. Summary
This report describes the test program written for the KDEPlot class declared in KDEPlot.hpp. The program is a single self-contained C++ file with a main() function that runs six checks using the standard assert macro. It requires no external testing framework. If every assertion holds, the program prints All KDEPlot tests passed. and exits with code 0.
The tests cover the basic shape of the output (number of points, ordering and non-negativity), use of a custom bandwidth, and error handling for two invalid inputs. They give a solid first layer of verification. Several important behaviours, such as numerical correctness of the density values, are not yet covered and are listed in Section 5.
2. Test Design
2.1 Approach
Each test sits in its own block scope, so variables do not leak between tests and every test starts from fresh data. The tests call only the public method KDEPlot::estimate, which means they check the class as a user would, without depending on its private helpers (gaussianKernel and automaticBandwidth).
2.2 Dependencies
Header
Used for
KDEPlot.hpp
The class under test
<cassert>
The assert macro for checks
<cmath>
Included, but not used by the current tests
<iostream>
Printing the success message
<stdexcept>
std::invalid_argument for the error tests
<vector>
Input data and results
3. Test Cases
#
Test
Input
Expected result
1
Requested number of points
{1, 2, 2, 3, 4, 5}, 25 points
Result contains exactly 25 points
2
Non-negative density
{10, 20, 30, 40, 50}, 30 points
Every density is 0.0 or greater
3
Ordered x values
{1, 2, 3, 4, 5}, 20 points
Each x is strictly greater than the one before
4
Custom bandwidth
{1, 2, 3, 4, 5}, 15 points, bandwidth 0.5
15 points returned, all densities non-negative
5
Empty data
Empty vector, default arguments
std::invalid_argument is thrown
6
Point count below 2
{1, 2, 3}, 1 point
std::invalid_argument is thrown
3.1 Test 1: Output size
This confirms that pointCount is respected. The dataset deliberately contains a repeated value (2), which shows the estimator copes with duplicate samples. It guards against off-by-one errors in the grid generation loop.
3.2 Test 2: Non-negative densities
A probability density can never be negative. Because a Gaussian kernel is always positive, every estimated value should be at least zero. The test uses a widely spaced dataset (10 to 50) to check this holds when the data values are large and the default bandwidth is chosen automatically.
3.3 Test 3: Increasing x values
A plotted curve needs its x coordinates in ascending order. Using a strict comparison (>) also guarantees that no two points share the same x value, which would indicate a zero-width grid step.
3.4 Test 4: Custom bandwidth
This exercises the code path where the caller supplies a bandwidth instead of relying on the automatic one. It checks that the result still has the correct size and valid densities.
3.5 Test 5: Empty input
A density cannot be estimated from no data. The test confirms that the class reports this as a std::invalid_argument rather than crashing, returning garbage, or dividing by zero.
3.6 Test 6: Too few points
A curve needs at least two evaluation points to define a spacing between them. The test confirms that a request for a single point is rejected with std::invalid_argument. This matches the design recommendation that a pointCount below 2 should be handled explicitly.
4. Strengths
• No external dependencies. The test file builds with any C++ compiler, which keeps it easy to run on any machine or build server.
• Readable and well organised. Each test has a descriptive comment and its own scope.
• Good mix of cases. Both normal behaviour (Tests 1 to 4) and error handling (Tests 5 and 6) are checked.
• Tests public behaviour only. Internal changes to the kernel or bandwidth routines will not break the tests unless the visible behaviour changes.
• Clear pass signal. The program prints a confirmation message and returns 0.
5. Limitations and Recommendations
5.1 Assertions can be disabled
The assert macro is removed entirely when code is compiled with NDEBUG, which is the default for many release builds. In that case all six tests would pass without checking anything. The build should make sure NDEBUG is not defined for the test target, or the tests should use a custom check macro that is always active and reports which check failed.
5.2 Failures stop at the first problem
A failed assert aborts the whole program, so only the first failure is seen. A small helper that records failures and continues, then returns a non-zero exit code at the end, would give a fuller picture on each run.
5.3 Exception tests do not check the cause
Tests 5 and 6 confirm that std::invalid_argument is thrown, but not that it is thrown for the right reason. An invalid_argument raised by an unrelated problem would still pass. Checking the exception message, or splitting the inputs so each isolates one cause, would tighten these tests.
5.4 Numerical correctness is not tested
No test checks that the density values are actually correct. The current checks would pass even if the curve had the wrong shape, provided it was non-negative and the right length. The following would address this:
• Normalisation: the area under the curve, estimated by the trapezoidal rule, should be close to 1.
• Known result: for a single sample with a known bandwidth, the density at the sample should equal 1 / (h·√(2π)).
• Peak location: for symmetric data, the highest density should be near the centre of the data.
• Bandwidth effect: a larger bandwidth should give a lower, flatter peak than a smaller one.
Comparisons of floating-point values should use a tolerance (the already included <cmath> header provides std::fabs for this).
5.5 Further edge cases
Case
Why it matters
A single data value
Automatic bandwidth may be undefined or zero
All values identical
Spread is zero, which can cause division by zero
Negative or zero explicit bandwidth
Should be rejected or handled consistently
NaN or infinite values in the data
Would corrupt the entire estimate
Very large pointCount or dataset
Checks performance and memory behaviour
Exactly 2 points
The smallest valid grid, a boundary case for Test 6
5.6 Tidy-ups
• <cmath> is included but unused. It will become needed once tolerance-based numerical tests are added; otherwise it can be removed.
• Test 4 only uses one bandwidth value. Adding very small and very large values would show how the class behaves at both extremes.
• Moving to a framework such as Catch2 or GoogleTest would provide named test cases, clearer failure messages and integration with CTest or a continuous integration pipeline.
6. How to Run
Assuming the test file is named KDEPlotTests.cpp and sits alongside KDEPlot.cpp:
g++ -std=c++17 -Wall -Wextra -O0 KDEPlot.cpp KDEPlotTests.cpp -o kde_tests
./kde_tests
Expected output when everything passes:
All KDEPlot tests passed.
The file names above are assumptions and should be adjusted to match the project.
7. Conclusion
The test suite checks the essential contract of KDEPlot::estimate: the right number of points, valid and ordered output, support for a custom bandwidth, and clear errors for empty data and too few points. It is a sound starting point and is easy to read and run. Making the checks robust against NDEBUG, adding numerical correctness tests, and covering the extra edge cases in Section 5 would turn it into a much stronger safeguard as the implementation evolves.
