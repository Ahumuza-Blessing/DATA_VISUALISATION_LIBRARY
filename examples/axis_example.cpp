#include "Axis.hpp"
#include <iostream>

int main() {
    Axis axis(0, 100, 0, 500);
    for (double value : {0.0, 25.0, 50.0, 75.0, 100.0})
        std::cout << value << " maps to " << axis.scale(value) << "\n";

    std::cout << "Axis tick values: ";
    for (double tick : axis.ticks(5))
        std::cout << tick << " ";
    std::cout << "\n";
}
