#include "rectangle.hpp"

#include <cmath>
#include <stdexcept>
#include <numbers>

#include "long_double_compare.hpp"
#include "figure_exception.hpp"

namespace Geometry {

namespace {
constexpr std::size_t vertexCount = 4;
}

Rectangle::Rectangle() noexcept = default;

Rectangle::Rectangle(const Point& start, double angle, double width, double height){
    if (width <= 0 || height <= 0) {
        throw exceptions::FigureException("Sides must be greater than 0");
    }
    double mathAngle = angle * std::numbers::pi_v<double> / 180;
    Point firstSide = Point(width * std::cos(mathAngle), width * std::sin(mathAngle));
    Point secondSide = Point(height * std::sin(mathAngle), height * std::cos(mathAngle));
    points_[0] = start;
    points_[1] = points_[0] + firstSide;
    points_[2] = points_[1] + secondSide;
    points_[3] = points_[2] - firstSide;
}

/// There is no reason to redefine it. 
Rectangle::Rectangle(const Rectangle&) = default;
Rectangle::Rectangle(Rectangle&&) noexcept = default;

// As well as here.
Rectangle& Rectangle::operator=(const Rectangle&) = default;
Rectangle& Rectangle::operator=(Rectangle&&) noexcept = default;

Rectangle::operator double() const noexcept {
    return (points_[1] - points_[0]).DistanceToCenter() * (points_[2] - points_[1]).DistanceToCenter();
}

Point Rectangle::Center() const noexcept {
    double x = 0;
    double y = 0;
    for (std::size_t i = 0; i < vertexCount; ++i) {
        x += points_[i].x;
        y += points_[i].y;
    }

    return Point(x / 4, y / 4);
}

bool operator==(const Rectangle& first, const Rectangle& second) noexcept {
    double firstSideOfFirst = (first.points_[0] - first.points_[1]).DistanceToCenter();
    double firstSideOfSecond = (second.points_[0] - second.points_[1]).DistanceToCenter();
    
    double secondSideOfFirst = (first.points_[1] - first.points_[2]).DistanceToCenter();
    double secondSideOfSecond = (second.points_[1] - second.points_[2]).DistanceToCenter();

    return compare::AreDoublesEqual(firstSideOfFirst, firstSideOfSecond) && compare::AreDoublesEqual(secondSideOfFirst, secondSideOfSecond);
}

bool operator!=(const Rectangle& first, const Rectangle& second) noexcept {
    return !(first == second);
}

void Rectangle::Print(std::ostream& out) const {
    out << "Rectangle: ";
    for (std::size_t i = 0; i < vertexCount; ++i) {
        out << points_[i];
    }
}

void Rectangle::Read(std::istream& in) {
    Point start;
    double angle;
    double a;
    double b;
    in >> start;
    in >> angle;
    in >> a;
    in >> b;


    *this = Rectangle(start, angle, a, b);
}

}