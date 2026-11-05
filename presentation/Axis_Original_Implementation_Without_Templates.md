# AXIS MODULE — C++ DATA VISUALIZATION LIBRARY

## Original Axis Implementation — Individual Technical Presentation and Code Defense

**Repository:** `Ahumuza-Blessing/DATA_VISUALISATION_LIBRARY`  
**Working branch:** `Romeo`  
**Module:** `Axis` (original implementation, without templates)  
**Files covered:** `include/Axis.hpp`, `src/Axis.cpp`, `tests/test_axis.cpp`

> **Scope:** This document explains the original Axis implementation before the separate template enhancement. It does not describe the newer `Romeo-template` branch.

> **How to use this guide:** Text under **What I would say** is a suggested spoken explanation. Read the code and understand the examples rather than memorizing sentences. The explanations below are based on the three Axis files previously retrieved from the `Romeo` branch; this document does not claim a fresh build or integration test was performed.

---

## 1. Opening Presentation

### What I would say

Good morning, lecturer and fellow students. Today I am presenting and defending my contribution to our C++ Data Visualization Library: the **Axis module**.

The purpose of the library is to help a C++ programmer turn numerical data into visual representations. A graph must position its data correctly. My Axis module performs the numerical calculations that relate a **data range**, such as exam scores from 0 to 100, to a **drawing range**, such as horizontal coordinates from 0 to 500.

I implemented an `Axis` class that stores these ranges, converts values into drawing coordinates, generates evenly spaced tick values, exposes controlled access to its state, and rejects certain invalid inputs. The module itself does **not** draw SVG lines or text: that is a separate rendering responsibility.

My contribution is organized into a public header, an implementation file, and a test file. I will explain each of them and demonstrate the mathematics behind the code.

### The problem being solved

A value such as `50` is meaningful in a dataset, but a drawing system needs a coordinate such as `250`. Different datasets and canvas sizes need different mappings. Repeating the conversion formula in every plotting module would duplicate logic. A reusable `Axis` class centralizes this calculation.

---

## 2. Architecture and Scope

```text
Numerical data values
        |
        v
  Axis object
  - data minimum and maximum
  - drawing start and end
  - scale(value)
  - ticks(count)
        |
        +----> drawing coordinates
        +----> numerical tick values
                    |
                    v
        Plotting / rendering code
                    |
                    v
               SVG output
```

**Important distinction:** The diagram shows the intended architectural relationship. The three Axis files prove the Axis calculations and test cases, but do not alone prove that every plotting module currently calls Axis or that the complete SVG pipeline works end to end.

### My three files

| File | Role | What it contains |
|---|---|---|
| `include/Axis.hpp` | Interface | Class declaration, fields, and public method declarations |
| `src/Axis.cpp` | Implementation | Constructor, scaling formula, tick algorithm, getters, and setters |
| `tests/test_axis.cpp` | Unit testing | Assertions for mapping, ticks, changed ranges, reversed coordinates, and invalid arguments |

The separation of declaration and implementation is a key C++ library design decision: users can include the header without needing to read every implementation detail.

---

## 3. Defending `include/Axis.hpp`

### Original structure with teaching comments

```cpp
#ifndef AXIS_HPP           // Continue only if AXIS_HPP has not been defined
#define AXIS_HPP           // Define the guard to prevent duplicate processing

#include <cstddef>         // Provides std::size_t
#include <vector>          // Provides std::vector

class Axis {               // Declares the Axis class
private:                   // Restricts direct access to the fields
    double minValue;       // Start of the numerical data range
    double maxValue;       // End of the numerical data range
    double screenStart;    // Starting drawing coordinate
    double screenEnd;      // Ending drawing coordinate

public:                    // Declares operations other code can call
    Axis(
        double minValue,
        double maxValue,
        double screenStart,
        double screenEnd
    );                     // Constructor

    double scale(double value) const; // Convert data value to drawing coordinate
    std::vector<double> ticks(std::size_t count = 6) const; // Generate tick values

    double getMin() const;            // Read the data minimum
    double getMax() const;            // Read the data maximum
    double getScreenStart() const;    // Read the drawing start
    double getScreenEnd() const;      // Read the drawing end

    void setRange(double minValue, double maxValue); // Update data range
    void setScreenRange(double screenStart, double screenEnd); // Update drawing range
};

#endif // AXIS_HPP        // Close the conditional compilation block
```

### 3.1 `#ifndef`, `#define`, and `#endif`

**What I would say:** `#ifndef AXIS_HPP` means *if AXIS_HPP has not already been defined*. `#define AXIS_HPP` then defines it. At the end, `#endif` closes the condition. Together they are a **header guard**. If the header is included more than once within the same translation unit, the compiler sees the class definition only once, avoiding redefinition errors.

**Potential question:** Why not simply rely on `#include`?  
**Answer:** The same header can be reached through multiple include paths. A header guard makes repeated inclusion safe. `#pragma once` is a common alternative, but the macro guard is portable standard preprocessing syntax.

### 3.2 `#include <cstddef>` and `#include <vector>`

- `<cstddef>` supplies `std::size_t`, an unsigned integer type used here for the tick count and loop index.
- `<vector>` supplies `std::vector`, a resizable sequence container. The function `ticks()` returns multiple `double` values, so a vector is appropriate.

**Potential question:** Why `std::size_t` rather than `int`?  
**Answer:** A tick count represents a nonnegative size. `std::size_t` is conventionally used for container sizes and indices. However, it is unsigned, so care is required with subtraction; this implementation checks `count < 2` before calculating `count - 1`.

### 3.3 `class Axis`, `private`, and `public`

**What I would say:** A class is a blueprint for objects containing related data and operations. `private` means outside code cannot directly assign to the four stored fields. `public` exposes the operations that other code is allowed to use. This is **encapsulation**: internal state is managed through the class interface.

**Potential question:** Is encapsulation the same as making everything private?  
**Answer:** No. Encapsulation means grouping state and behavior and controlling how they interact. This class exposes useful public operations while protecting its fields.

### 3.4 Why four `double` fields?

- `minValue` and `maxValue` describe the numerical interval.
- `screenStart` and `screenEnd` describe the corresponding drawing interval.
- `double` supports fractional data and coordinates. It is not exact for all decimal numbers, so tests use a small tolerance.

**Example:** `Axis axis(0, 100, 50, 550);` means data value `0` corresponds to coordinate `50`, and data value `100` corresponds to coordinate `550`.

### 3.5 Constructor declaration

```cpp
Axis(double minValue, double maxValue,
     double screenStart, double screenEnd);
```

A constructor runs when an object is created and establishes its initial state. The constructor has the same name as the class and no return type.

### 3.6 `scale`, `ticks`, `const`, and default arguments

```cpp
double scale(double value) const;
std::vector<double> ticks(std::size_t count = 6) const;
```

`scale()` accepts one data value and returns its drawing coordinate. `ticks()` returns a vector of numerical tick values. `count = 6` means a caller can write `axis.ticks()` and request six ticks by default; `axis.ticks(3)` requests three.

The trailing `const` promises that these member functions will not modify the object's ordinary member state. It allows them to be called on a `const Axis` object.

### 3.7 Getters and setters

The four getters return the stored values without changing them. `setRange()` changes the numerical interval after checking that the endpoints differ. `setScreenRange()` updates the drawing endpoints. This interface avoids direct field modification while allowing controlled reconfiguration.

---

## 4. Defending `src/Axis.cpp`

### 4.1 Includes and constructor

```cpp
#include "Axis.hpp"  // Makes the class declaration visible
#include <stdexcept>  // Provides std::invalid_argument

Axis::Axis(double minValue, double maxValue,
           double screenStart, double screenEnd)
    : minValue(minValue),
      maxValue(maxValue),
      screenStart(screenStart),
      screenEnd(screenEnd) {
    if (minValue == maxValue) {
        throw std::invalid_argument(
            "Axis minimum and maximum cannot be equal.");
    }
}
```

**What I would say:** `Axis::Axis` defines the constructor belonging to the `Axis` class. The colon begins a **member initializer list**, which initializes the four fields directly. For example, `minValue(minValue)` means the field on the left is initialized using the parameter on the right. Although their names match, their roles are different.

The condition `minValue == maxValue` detects a zero-width data interval. If the values are equal, the denominator in `scale()` would be zero. The constructor therefore throws `std::invalid_argument`.

**Technical nuance:** The check rejects equal endpoints, but it does not reject `minValue > maxValue`, non-finite values (`NaN`, infinity), or equal drawing endpoints. Those are limitations or deliberate allowances, not additional checks present in this code.

### 4.2 The scaling formula

```cpp
double Axis::scale(double value) const {
    return screenStart +
           (value - minValue) *
           (screenEnd - screenStart) /
           (maxValue - minValue);
}
```

In mathematical form:

\[
\text{screenPosition} = S_0 + \frac{x - a}{b - a}(S_1 - S_0)
\]

Where:

| Symbol | Meaning |
|---|---|
| `x` | Data value being converted |
| `a` | Minimum data value |
| `b` | Maximum data value |
| `S₀` | Starting drawing coordinate |
| `S₁` | Ending drawing coordinate |

**Why this formula?** First, `x - a` measures how far the value is above the data minimum. Dividing by `b - a` gives its relative position in the data range. Multiplying by `S₁ - S₀` converts that fraction into a drawing distance. Adding `S₀` places the result at the correct absolute drawing coordinate.

#### Worked example A: No margin

```cpp
Axis axis(0, 100, 0, 500);
axis.scale(60);
```

1. Data distance: `60 - 0 = 60`.
2. Data span: `100 - 0 = 100`.
3. Relative position: `60 / 100 = 0.6`.
4. Drawing span: `500 - 0 = 500`.
5. Drawing distance: `0.6 × 500 = 300`.
6. Start coordinate: `0 + 300 = 300`.

**Result:** `axis.scale(60)` is `300`.

#### Worked example B: Margin on the left

```cpp
Axis axis(0, 100, 50, 550);
axis.scale(60);
```

The relative position is still `0.6`, and the drawing span is `500`. The position is now `50 + 0.6 × 500 = 350`.

**Result:** `350`, not `300`, because the drawing range begins at `50`.

#### Worked example C: Negative values

```cpp
Axis axis(-10, 10, 0, 500);
axis.scale(0);
```

Relative position = `(0 - (-10)) / (10 - (-10)) = 10 / 20 = 0.5`.  
Drawing coordinate = `0 + 0.5 × 500 = 250`.

#### Worked example D: Reversed screen direction

```cpp
Axis axis(0, 100, 500, 0);
axis.scale(25);
```

Drawing span = `0 - 500 = -500`.  
Coordinate = `500 + (25/100) × (-500) = 375`.

Reversed screen coordinates are useful when drawing directions differ, such as vertical graphics where increasing pixel `y` moves downward.

#### Worked example E: Value outside the data range

```cpp
Axis axis(0, 100, 0, 500);
axis.scale(120);
```

Result = `600`. The function **extrapolates** outside the drawing range; it does not clamp the output to `[0, 500]`. This is an important limitation to mention if asked.

### 4.3 Tick generation

```cpp
std::vector<double> Axis::ticks(std::size_t count) const {
    if (count < 2) {
        throw std::invalid_argument(
            "Axis needs at least two tick values.");
    }

    std::vector<double> values;
    values.reserve(count);

    double step = (maxValue - minValue) /
                  static_cast<double>(count - 1);

    for (std::size_t i = 0; i < count; ++i) {
        values.push_back(minValue + static_cast<double>(i) * step);
    }

    return values;
}
```

**What I would say:** A tick is a numerical marker on an axis. The function checks that at least two ticks were requested, creates an empty vector, reserves enough capacity, calculates a step size, then uses a `for` loop to append each tick.

The step formula is:

\[
\text{step} = \frac{\text{maxValue} - \text{minValue}}{\text{count} - 1}
\]

We subtract one because **N tick marks create N − 1 intervals**. For example, six marks create five gaps.

#### Worked example: Six ticks between 0 and 100

`step = (100 - 0)/(6 - 1) = 20`.

| Loop index `i` | Formula `0 + i × 20` | Tick |
|---:|---:|---:|
| 0 | `0 + 0 × 20` | 0 |
| 1 | `0 + 1 × 20` | 20 |
| 2 | `0 + 2 × 20` | 40 |
| 3 | `0 + 3 × 20` | 60 |
| 4 | `0 + 4 × 20` | 80 |
| 5 | `0 + 5 × 20` | 100 |

**Returned vector:** `{0, 20, 40, 60, 80, 100}`.

#### Worked example: Three ticks between −10 and 10

`step = (10 - (-10))/(3 - 1) = 10`.  
**Returned vector:** `{-10, 0, 10}`.

#### What do the less obvious statements mean?

- `std::vector<double> values;` creates a vector that is initially empty.
- `values.reserve(count);` reserves capacity for `count` elements, potentially reducing reallocations. It **does not** add elements or change `values.size()`.
- `static_cast<double>(count - 1)` explicitly converts an integer count into a floating-point value.
- `std::size_t i = 0` declares a nonnegative index variable.
- `i < count` is the loop condition; `++i` increments the index.
- `values.push_back(...)` appends one calculated tick.
- `return values;` returns the completed vector.

**Complexity:** Generating N ticks takes **O(N)** time and uses **O(N)** output storage.

### 4.4 Getters

```cpp
double Axis::getMin() const { return minValue; }
double Axis::getMax() const { return maxValue; }
double Axis::getScreenStart() const { return screenStart; }
double Axis::getScreenEnd() const { return screenEnd; }
```

Each getter returns a field and does not modify the object. This lets other modules inspect the axis without making the fields public.

### 4.5 Setters

```cpp
void Axis::setRange(double newMinValue, double newMaxValue) {
    if (newMinValue == newMaxValue) {
        throw std::invalid_argument(
            "Axis minimum and maximum cannot be equal.");
    }
    minValue = newMinValue;
    maxValue = newMaxValue;
}

void Axis::setScreenRange(double newScreenStart, double newScreenEnd) {
    screenStart = newScreenStart;
    screenEnd = newScreenEnd;
}
```

`void` means the method does not return a value. `setRange()` validates the proposed numerical range **before** assigning it, so an equal-endpoint request leaves the previous range intact. `setScreenRange()` assigns both drawing endpoints without validation, allowing reversed directions and also equal endpoints.

---

## 5. Defending `tests/test_axis.cpp`

### Actual test structure with teaching comments

```cpp
#include "Axis.hpp" // Class under test
#include <cassert>   // assert()
#include <cmath>     // std::fabs()
#include <iostream>  // std::cout
#include <stdexcept> // std::invalid_argument

int main() {
    Axis axis(0, 100, 0, 500); // Create a test axis

    assert(std::fabs(axis.scale(0) - 0) < 1e-9);
    assert(std::fabs(axis.scale(25) - 125) < 1e-9);
    assert(std::fabs(axis.scale(50) - 250) < 1e-9);
    assert(std::fabs(axis.scale(100) - 500) < 1e-9);

    auto ticks = axis.ticks(3); // Expect 0, 50, 100
    assert(ticks.size() == 3);
    assert(std::fabs(ticks[1] - 50) < 1e-9);

    axis.setRange(-10, 10); // Update numerical range
    assert(std::fabs(axis.scale(0) - 250) < 1e-9);

    axis.setScreenRange(500, 0); // Reverse drawing direction
    assert(std::fabs(axis.scale(-10) - 500) < 1e-9);

    bool invalidRange = false;
    try { Axis bad(1, 1, 0, 100); }
    catch (const std::invalid_argument&) { invalidRange = true; }
    assert(invalidRange);

    bool invalidTicks = false;
    try { axis.ticks(1); }
    catch (const std::invalid_argument&) { invalidTicks = true; }
    assert(invalidTicks);

    std::cout << "Axis tests passed.\n";
}
```

### 5.1 Why `assert`?

An assertion checks that a condition is true. If a condition is false and assertions are enabled, the program reports failure and terminates. This is a simple way to write unit tests without a separate testing framework.

**Important caveat:** Standard `assert` checks are disabled when `NDEBUG` is defined (often in release builds). Run these tests with assertions enabled; a printed success message alone is not proof that disabled assertions ran.

### 5.2 Why `std::fabs(... ) < 1e-9`?

Floating-point calculations can have small rounding differences. Instead of demanding exact equality, the test accepts a difference smaller than `0.000000001`. `std::fabs` returns the absolute value of the difference.

Example: `std::fabs(axis.scale(50) - 250) < 1e-9` means the mapped coordinate should be extremely close to 250.

### 5.3 Test categories

| Test | Input | Expected behavior |
|---|---|---|
| Minimum boundary | `scale(0)` on 0–100 → 0–500 | 0 |
| Interior point | `scale(25)` | 125 |
| Midpoint | `scale(50)` | 250 |
| Maximum boundary | `scale(100)` | 500 |
| Tick count | `ticks(3)` | Vector size 3 |
| Tick midpoint | `ticks(3)[1]` | 50 |
| Changed data range | `setRange(-10,10); scale(0)` | 250 |
| Reversed drawing range | `setScreenRange(500,0); scale(-10)` | 500 |
| Invalid constructor | `Axis(1,1,0,100)` | `std::invalid_argument` |
| Invalid tick count | `ticks(1)` | `std::invalid_argument` |

### 5.4 How the exception tests work

The boolean starts as `false`. The `try` block performs an operation expected to throw. If `std::invalid_argument` is caught, the `catch` block sets the boolean to `true`. The following assertion verifies that the expected exception occurred.

### 5.5 What these tests do **not** prove

The file does not currently test getters, default `ticks()`, a setter with equal endpoints, non-finite inputs, extrapolation, very large tick counts, or integration with the renderer. These would be reasonable future tests. Do not claim they have already been implemented.

---

## 6. Object-Oriented Programming Concepts Used

| Concept | Where it appears | Defense explanation |
|---|---|---|
| Class | `class Axis` | Groups related state and operations |
| Object | `Axis axis(0,100,0,500)` | Creates a concrete instance of the class |
| Encapsulation | `private` fields and `public` methods | Controls direct access to internal state |
| Abstraction | `scale(value)` and `ticks(count)` | Callers use the functionality without reproducing its mathematics |
| Constructor | `Axis::Axis(...)` | Establishes the initial object state |
| Member functions | `scale`, `ticks`, getters, setters | Operate on an Axis instance |
| Const-correctness | `scale(...) const`, getters | Indicates the functions do not modify ordinary object state |
| Exception handling | `throw std::invalid_argument` | Reports unsupported input conditions |
| Standard containers | `std::vector<double>` | Stores a variable-length list of ticks |

**Do not claim:** This Axis class demonstrates inheritance, polymorphism, virtual functions, pointers, or templates. Those features are not present in the three reviewed Axis files. The project may use them elsewhere, but they are not shown here.

---

## 7. Live Demonstration

### 7.1 Minimal example

The following is a **demonstration snippet**, not an additional file confirmed to exist in the repository:

```cpp
#include "Axis.hpp"
#include <iostream>

int main() {
    Axis axis(0, 100, 50, 550);

    std::cout << "Position of 60: " << axis.scale(60) << '\n';

    for (double tick : axis.ticks(6)) {
        std::cout << tick << ' ';
    }
    std::cout << '\n';
}
```

Expected output:

```text
Position of 60: 350
0 20 40 60 80 100
```

### 7.2 Compile the existing test directly

From the **repository root** in a terminal with a C++17-compatible compiler:

```powershell
g++ -std=c++17 -Wall -Wextra -Iinclude src/Axis.cpp tests/test_axis.cpp -o axis_test.exe
.\axis_test.exe
```

If compilation and enabled assertions succeed, the program should print:

```text
Axis tests passed.
```

This command assumes the file paths match the previously retrieved `Romeo` branch. It compiles the Axis test only; it is not a complete library build. If the project uses CMake, follow its current `README.md` and `CMakeLists.txt` for the full build instead of inventing target names.

### 7.3 Demonstration speaking sequence

1. Show `Axis.hpp` and explain the public interface and four fields.
2. Show the constructor and explain the zero-width data-range check.
3. Trace `scale(60)` for data 0–100 and drawing coordinates 50–550; predict 350 before running.
4. Trace `ticks(6)` and explain why the divisor is five.
5. Run the Axis unit tests and show the actual terminal result.
6. Explain which cases were tested and which were not.

---

## 8. Design Decisions and Trade-offs

### Why a separate Axis class?

It gives plotting code a reusable way to map values and calculate ticks without copying the same formula into every graph type.

### Why linear scaling?

The formula preserves proportional distances. For example, a data difference of 20 occupies the same drawing distance anywhere along the same linear axis. The implementation does **not** offer logarithmic or categorical scaling.

### Why `double`?

It supports fractional values and drawing coordinates, while acknowledging normal floating-point rounding behavior.

### Why exceptions?

An invalid range should be reported explicitly rather than silently allowing a division by zero. The caller can catch `std::invalid_argument` and respond appropriately.

### Why `reserve()`?

The number of ticks is known in advance. Reserving capacity can avoid repeated memory allocations during the loop, though it does not itself add elements.

### Why keep drawing outside Axis?

Axis focuses on numeric mapping and tick generation. Separating numeric calculation from SVG rendering improves modularity and makes the Axis calculations testable without producing an image.

---

## 9. Challenges, Limitations, and Improvements

### Challenges I can discuss

- **Understanding coordinate systems:** Data values and drawing coordinates are different quantities; the formula bridges them.
- **Avoiding division by zero:** Equal data endpoints would invalidate the formula, so the constructor and `setRange()` reject them.
- **Generating correct tick intervals:** `count` ticks require `count - 1` intervals.
- **Handling drawing direction:** The signed difference `screenEnd - screenStart` allows the axis direction to be reversed.
- **Testing floating-point results:** A tolerance is used instead of direct equality.

These are implementation challenges visible from the code. Do not present unverified personal development history as established fact.

### Known limitations

1. The axis uses **linear** interpolation only.
2. Tick values are **uniformly spaced** and are not automatically rounded to aesthetically pleasing intervals such as 1, 2, 5, 10.
3. `scale()` does **not clamp** values outside the data range.
4. Equal drawing endpoints are allowed, so every value may map to one coordinate.
5. The code checks equality of data endpoints but does not explicitly reject `NaN` or infinity.
6. The code permits descending data endpoints (`minValue > maxValue`), despite the field names.
7. `ticks()` creates the requested number of elements; very large counts may consume substantial memory or throw an allocation exception.
8. This module does not draw axis lines, labels, or SVG elements.
9. Unit tests are limited to the cases in `test_axis.cpp` and do not prove end-to-end integration.

### Potential improvements

Add tests for getters and default ticks; validate non-finite inputs if required; decide whether descending ranges should be allowed; offer optional clamping; add aesthetically pleasing tick spacing; and expand integration tests with plotting and rendering modules. These are proposals, not features already implemented.

---

## 10. Lecturer Questions and Suggested Answers

### Q1. What exactly did you contribute?

I contributed the Axis module, whose reviewed files declare the class, implement linear coordinate mapping and tick generation, and test key behaviors. The class does not render SVG by itself.

### Q2. Why do we need an Axis module?

Graph data is expressed in values such as marks, while a renderer needs drawing coordinates. The Axis module converts between these two ranges consistently.

### Q3. Explain the formula without reading it.

I first find the fraction of the data range that the value occupies. I multiply that fraction by the drawing length, then add the starting drawing coordinate.

### Q4. Why subtract `minValue` from `value`?

To measure the value's offset from the start of the data range. Without this subtraction, a range such as 50–150 would be mapped incorrectly.

### Q5. Why divide by `maxValue - minValue`?

That is the total data span. Dividing the offset by the span normalizes the value to a relative position, normally between zero and one for in-range inputs.

### Q6. Why multiply by `screenEnd - screenStart`?

That converts a relative position into a distance in drawing coordinates.

### Q7. Why add `screenStart` at the end?

Because the drawing range may begin somewhere other than zero. It accounts for margins or offsets.

### Q8. Calculate `scale(75)` for `Axis(0,100,0,400)`.

`(75 - 0)/(100 - 0) = 0.75`; `0 + 0.75 × 400 = 300`.

### Q9. Calculate `scale(75)` for `Axis(0,100,20,420)`.

The drawing span is 400. `20 + 0.75 × 400 = 320`.

### Q10. What happens if `minValue == maxValue`?

The constructor or `setRange()` throws `std::invalid_argument`, because the scaling denominator would be zero.

### Q11. What if `screenStart == screenEnd`?

The current code allows it. The drawing span becomes zero, so every finite scaled value maps to the same coordinate. It may be undesirable for a visible axis.

### Q12. Can the axis run backward?

Yes. If `screenStart` is greater than `screenEnd`, the drawing span is negative and coordinates decrease as data values increase.

### Q13. What if the data value is outside the specified range?

The function extrapolates; it does not clamp the result. For example, 120 in a 0–100 data range mapped to 0–500 becomes 600.

### Q14. What is a tick mark?

A tick mark represents a numerical position along an axis, often used by rendering code to label or divide the scale. This module returns tick **values**, not graphical tick lines.

### Q15. Why `count - 1` instead of `count`?

Because N marks create N − 1 spaces between the first and last marks. Six ticks produce five intervals.

### Q16. Generate five ticks between 10 and 50.

Step = `(50 - 10)/(5 - 1) = 10`. Ticks: `10, 20, 30, 40, 50`.

### Q17. What does `std::vector<double>` mean?

It is a dynamic sequence container whose elements are of type `double`. Here it holds the generated tick values.

### Q18. Does `reserve(count)` create `count` elements?

No. It reserves capacity, while the size stays zero until `push_back()` adds elements.

### Q19. Why use `static_cast<double>`?

It makes the conversion to floating-point explicit and ensures the step calculation is expressed in floating-point terms.

### Q20. What does `const` mean after a method declaration?

The method promises not to modify ordinary member state. It is part of const-correctness and permits calls on const objects.

### Q21. Why are the fields private?

To prevent outside code from directly changing them and bypassing the class's intended interface. Setters and getters provide controlled access.

### Q22. What is the difference between a getter and setter?

A getter reads a stored value. A setter changes stored state, sometimes after validation.

### Q23. What does `Axis::` mean?

It is the scope-resolution operator indicating that a function belongs to the `Axis` class.

### Q24. Why use an initializer list?

It initializes fields directly as the object is constructed rather than assigning to already initialized fields in the constructor body.

### Q25. What is `std::invalid_argument`?

It is a standard exception type used to report an invalid function or constructor argument.

### Q26. Why use `try` and `catch` in the test?

The test deliberately triggers an error and checks that the expected exception type is thrown.

### Q27. Why use `std::fabs`?

It measures the absolute difference between a calculated floating-point value and its expected value.

### Q28. What does `1e-9` mean?

It means one billionth, or 0.000000001. The tests accept differences smaller than this tolerance.

### Q29. What happens if a test assertion fails?

With assertions enabled, the program reports an assertion failure and terminates. If `NDEBUG` is defined, assertions are disabled, which is why test build settings matter.

### Q30. Does your Axis module demonstrate inheritance or polymorphism?

No. The reviewed Axis class demonstrates encapsulation, abstraction, constructors, member functions, standard containers, and exception handling. Inheritance and polymorphism are not used in this module.

### Q31. Is your code using the Seaborn library?

No. It is C++ code implementing its own simple linear axis mapping. The wider project may be inspired by visualization libraries, but this module does not import or depend on Python Seaborn.

### Q32. How efficient is `scale()`?

It performs a fixed number of arithmetic operations, so its time complexity is O(1) and its extra space usage is O(1).

### Q33. How efficient is `ticks(count)`?

It runs one iteration per tick and stores that many values, so time and output space are both O(N).

### Q34. Does `ticks()` return the screen positions of tick marks?

No. It returns numerical data values. A renderer could pass those values through `scale()` to obtain drawing positions.

### Q35. How would you extend this to a logarithmic axis?

I would design a separate transformation or scale type using logarithms and validate that its data domain is positive. The current implementation is strictly linear.

### Q36. What is your strongest evidence that the module works?

The test source specifies expected results for scaling, ticks, reversed ranges, and invalid inputs. I would compile and run it live, showing the actual test output rather than merely claiming it passed.

### Q37. What would you improve first?

I would expand unit tests to cover getters, default ticks, non-finite inputs, and edge cases, then add integration tests that verify a plotting module uses the coordinates correctly.

### Q38. What happens if `setRange(5,5)` is called on an existing axis?

It throws before assigning either new endpoint, so the previously stored range remains unchanged.

### Q39. Why isn't `screenStart` always zero?

Graphs often have margins for labels or other visual elements. Allowing arbitrary drawing endpoints makes the Axis reusable across different layouts.

### Q40. If a lecturer asks you to modify the code live, what could you do?

I could add a new unit test, demonstrate a changed range, or add an optional clamping method after discussing its intended behavior. I would run the tests after any modification to verify that existing behavior still works.

---

## 11. Mock Defense Dialogue

**Lecturer:** What problem does your code solve?  
**Student:** It converts numerical data values into drawing coordinates and generates evenly spaced numerical tick values for an axis.

**Lecturer:** Suppose I give you `Axis(20, 80, 100, 700)` and ask you to scale `50`.  
**Student:** The value is 30 above the minimum, and the total data span is 60, so the fraction is one half. The drawing span is 600, so the drawing distance is 300. Adding the starting coordinate of 100 gives **400**.

**Lecturer:** Why is your constructor checking equality?  
**Student:** If the endpoints are equal, the data span is zero. The scaling formula would divide by zero, so I reject that input with an exception.

**Lecturer:** If you request six ticks, why divide by five?  
**Student:** Because the six tick marks define five intervals between the first and last tick.

**Lecturer:** Did you implement SVG drawing in Axis?  
**Student:** No. Axis performs numerical calculations. Drawing the visual elements is the responsibility of other components. This separation supports reuse and independent testing.

**Lecturer:** How do I know your module is correct?  
**Student:** I can show the unit tests, explain their expected results, compile them, and run them. I will also distinguish what those unit tests cover from what still requires integration testing.

---

## 12. Closing Statement

### What I would say

In conclusion, my Axis module provides two core capabilities: **linear coordinate scaling** and **evenly spaced tick generation**. I used a C++ class with private fields and a public interface to organize the logic, an initializer list to construct objects, `const` methods for read-only operations, a `std::vector` for tick values, and exceptions to reject invalid data ranges or tick counts.

The mathematical idea is straightforward: find where a value lies proportionally in its data interval, then place it at the same proportional position in the drawing interval. This allows the same code to work with different datasets, margins, and axis directions.

The unit tests cover several normal and boundary cases as well as invalid arguments. I also recognize that broader integration testing and additional edge-case validation would improve reliability. Thank you, lecturer. I am ready to demonstrate the code and explain any line or calculation.

---

## 13. Final Preparation Checklist

- [ ] I can explain `#ifndef`, `#define`, and `#endif` without notes.
- [ ] I know the difference between the `.hpp`, `.cpp`, and test files.
- [ ] I can explain each of the four stored fields.
- [ ] I can derive the scaling formula and solve a new numerical example.
- [ ] I can explain why `count - 1` appears in tick generation.
- [ ] I can explain `std::vector`, `reserve`, `push_back`, `static_cast`, and `const`.
- [ ] I can explain the constructor initializer list and `Axis::`.
- [ ] I can explain exception handling and floating-point test tolerances.
- [ ] I can run the Axis tests and show their real output.
- [ ] I know what my Axis module does **not** implement.
- [ ] I can identify which improvements are proposals rather than existing features.
- [ ] I have checked the actual project README and full build instructions before demonstrating integration.
- [ ] I have accurately declared any AI assistance in the required project documentation.

**Reminder:** This guide is study support. Your project instructions require you to understand and defend your own implementation and to declare AI use. Verify the current code and actual test results before presenting.
