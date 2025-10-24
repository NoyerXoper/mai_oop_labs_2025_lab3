#pragma once

#include <istream>
#include <ostream>

#include "figure.hpp"
#include "point.hpp"

namespace Geometry {
class Rhombus: public Figure {
public:
    Rhombus() noexcept;
    Rhombus(const Point& start, double turn, double side, double angle);

    Rhombus(const Rhombus& other);
    Rhombus(Rhombus&& other) noexcept;

    explicit operator double() const noexcept final;
    Point Center() const noexcept final;

    Rhombus& operator=(const Rhombus& other);
    Rhombus& operator=(Rhombus&& other) noexcept;

    void Read(std::istream& in) final;
    void Print(std::ostream& in) const final;

    friend bool operator==(const Rhombus& first, const Rhombus& second) noexcept;
    friend bool operator!=(const Rhombus& first, const Rhombus& second) noexcept;

protected:
    Point points_[4];
};
}