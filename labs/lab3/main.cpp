#include <iostream>

#include "array_figures.hpp"
#include "figure.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

int main() {
    array::Array arrayOfFigures(3);
    arrayOfFigures.PushBack(new Geometry::Rectangle());
    arrayOfFigures.PushBack(new Geometry::Rhombus());
    arrayOfFigures.PushBack(new Geometry::Trapezoid());

    for (std::size_t i = 0; i < 3; ++i) {
        std::cin >> *arrayOfFigures[i];
    }

    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << *arrayOfFigures[i] << "\n";
    }

    std::cout << "Areas of figures:\n";
    
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << static_cast<double>(*arrayOfFigures[i]) << "\n";
    }

    std::cout << "Centers:\n";
    for (std::size_t i = 0; i < 3; ++i) {
        std::cout << arrayOfFigures[i]->Center() << "\n";
    }

    std::cout << "Total area:\n";
    double area = 0;
    
    for (std::size_t i = 0; i < 3; ++i) {
        area += static_cast<double>(*arrayOfFigures[i]);
    }
    std::cout << area << "\n";


}