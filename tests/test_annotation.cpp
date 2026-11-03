#include "Annotation.hpp"
#include <cassert>
#include <iostream>
int main() {
    Annotation annotations;
    assert(annotations.getItems().empty());
    annotations.add(10, 20, "Peak");
    annotations.add(30, 40, "Average");
    assert(annotations.getItems().size() == 2);
    assert(annotations.getItems()[0].text == "Peak");
    assert(annotations.getItems()[1].x == 30);
    annotations.clear();
    assert(annotations.getItems().empty());
    std::cout << "Annotation tests passed.\n";
}