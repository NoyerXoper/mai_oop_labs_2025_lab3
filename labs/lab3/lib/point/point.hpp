#pragma once

#include <istream>
#include <ostream>

namespace Geometry {
struct Point {
public:
    Point() noexcept;
    Point(double x, double y) noexcept;
    double DistanceToCenter() const noexcept;
    Point& operator+=(const Point& point) noexcept;
    Point& operator-=(const Point& point) noexcept;
    Point& operator*=(double number) noexcept;

    double x;
    double y;
};

Point operator+(const Point& first, const Point& second) noexcept;
Point operator-(const Point& first, const Point& second) noexcept;
// V * numbers is not defined in Linear Algebra, as well as division
Point operator*(double number, const Point& point) noexcept;

double operator*(const Point& first, const Point& second) noexcept;

bool operator==(const Point& first, const Point& second) noexcept;
bool operator!=(const Point& first, const Point& second) noexcept;

std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Point& point);
}
