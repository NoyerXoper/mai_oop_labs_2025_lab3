#include "point.hpp"

#include <cmath>

#include "long_double_compare.hpp"


namespace Geometry {

Point::Point() noexcept : Point(0, 0) {}

Point::Point(double x, double y) noexcept : x(x), y(y) {}

double Point::DistanceToCenter() const noexcept {
    return std::sqrt(x * x + y * y);
}

Point& Point::operator+=(const Point& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
}

Point& Point::operator-=(const Point& other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
}

Point& Point::operator*=(double number) noexcept {
    x *= number;
    y *= number;
    return *this;
}

std::istream& operator>>(std::istream& in, Point& point) {
    in >> point.x;
    in >> point.y;
    return in;
} 

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << "(" << point.x << ", " << point.y << ")";
    return out;
} 

Point operator+(const Point& first, const Point& second) noexcept {
    return Point(first.x + second.x, first.y + second.y);
}

Point operator-(const Point& first, const Point& second) noexcept {
    return Point(first.x - second.x, first.y - second.y);
}

double operator*(const Point& first, const Point& second) noexcept {
    return first.x * second.x + first.y * second.y;
}

Point operator*(double number, const Point& point) noexcept {
    return Point(number * point.x, number * point.y);
}

bool operator==(const Point& first, const Point& second) noexcept {
    return compare::AreDoublesEqual(first.x, second.x) && compare::AreDoublesEqual(first.y, second.y);
}

bool operator!=(const Point& first, const Point& second) noexcept {
    return !(first == second);
}
}
