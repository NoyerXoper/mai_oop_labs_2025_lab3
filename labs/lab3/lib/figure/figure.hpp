#pragma once

#include <istream>
#include <ostream>

#include "point.hpp"

namespace Geometry {
class Figure {
public:
    virtual Point Center() const noexcept = 0;
    virtual explicit operator double() const noexcept = 0;

    virtual ~Figure() noexcept;

    friend std::ostream& operator<<(std::ostream& out, const Figure& fig);
    friend std::istream& operator>>(std::istream& out, Figure& fig);
protected:
    virtual void Read(std::istream& in) = 0;
    virtual void Print(std::ostream& out) const = 0;
};
}
