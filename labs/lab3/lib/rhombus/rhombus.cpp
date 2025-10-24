#include "rhombus.hpp"

#include <cmath>
#include <stdexcept>
#include <numbers>

#include "long_double_compare.hpp"
#include "figure_exception.hpp"

namespace Geometry {

namespace {
constexpr std::size_t vertexCount = 4;
}

Rhombus::Rhombus() noexcept = default;

Rhombus::Rhombus(const Point& start, double turn, double side, double angle){
    if (side <= 0) {
        throw exceptions::FigureException("Sides must be greater than 0");
    }
    double mathAngle = angle * std::numbers::pi_v<double> / 180;
    double mathTurn = turn * std::numbers::pi_v<double> / 180;
    Point firstSide = Point(side * std::cos(mathTurn), side * std::sin(mathTurn));
    Point secondSide = Point(side * std::cos(mathTurn + mathAngle), side * std::sin(mathTurn + mathAngle));
    points_[0] = start;
    points_[1] = points_[0] + firstSide;
    points_[2] = points_[1] + secondSide;
    points_[3] = points_[2] - firstSide;
}

/// There is no reason to redefine it. 
Rhombus::Rhombus(const Rhombus&) = default;
Rhombus::Rhombus(Rhombus&&) noexcept = default;

// As well as here.
Rhombus& Rhombus::operator=(const Rhombus&) = default;
Rhombus& Rhombus::operator=(Rhombus&&) noexcept = default;

Rhombus::operator double() const noexcept {
    Point side1 = points_[1] - points_[0];
    Point side2 = points_[2] - points_[1];
    return std::abs(side1.x * side2.y - side2.x * side1.y);
}

Point Rhombus::Center() const noexcept {
    double x = 0;
    double y = 0;
    for (std::size_t i = 0; i < vertexCount; ++i) {
        x += points_[i].x;
        y += points_[i].y;
    }

    return Point(x / 4, y / 4);
}

bool operator==(const Rhombus& first, const Rhombus& second) noexcept {
    double side1_1 = (first.points_[0] - first.points_[1]).DistanceToCenter();

    double side2_1 = (second.points_[0] - second.points_[1]).DistanceToCenter();

    return compare::AreDoublesEqual(side1_1, side2_1) && compare::AreDoublesEqual(static_cast<double>(first), static_cast<double>(second));
}

bool operator!=(const Rhombus& first, const Rhombus& second) noexcept {
    return !(first == second);
}

void Rhombus::Print(std::ostream& out) const {
    out << "Rhombus: ";
    for (std::size_t i = 0; i < vertexCount; ++i) {
        out << points_[i];
    }
}

void Rhombus::Read(std::istream& in) {
    Point start;
    double turn;
    double side;
    double angle;
    in >> start;
    in >> turn;
    in >> side;
    in >> angle;

    *this = Rhombus(start, turn, side, angle);
}

}