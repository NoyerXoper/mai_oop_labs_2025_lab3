#pragma once

#include <istream>
#include <ostream>

#include "figure.hpp"
#include "point.hpp"

namespace Geometry {
class Rectangle: public Figure {
public:
    Rectangle() noexcept;
    Rectangle(const Point& start, double angle, double width, double height);

    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;

    explicit operator double() const noexcept final;
    Point Center() const noexcept final;

    Rectangle& operator=(const Rectangle& other);
    Rectangle& operator=(Rectangle&& other) noexcept;

    void Read(std::istream& in) final;
    void Print(std::ostream& in) const final;

    friend bool operator==(const Rectangle& first, const Rectangle& second) noexcept;
    friend bool operator!=(const Rectangle& first, const Rectangle& second) noexcept;

protected:
    Point points_[4];
};
}
