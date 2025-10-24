#pragma once

#include <istream>
#include <ostream>

#include "figure.hpp"
#include "point.hpp"

namespace Geometry {
class Trapezoid: public Figure {
public:
    Trapezoid() noexcept;
    Trapezoid(const Point& start, double angle, double base1, double base2, double side);

    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other) noexcept;

    explicit operator double() const noexcept final;
    Point Center() const noexcept final;

    Trapezoid& operator=(const Trapezoid& other);
    Trapezoid& operator=(Trapezoid&& other) noexcept;

    void Read(std::istream& in) final;
    void Print(std::ostream& in) const final;

    friend bool operator==(const Trapezoid& first, const Trapezoid& second) noexcept;
    friend bool operator!=(const Trapezoid& first, const Trapezoid& second) noexcept;

protected:
    Point points_[4];
};
}