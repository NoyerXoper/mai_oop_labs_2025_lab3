#include "trapezoid.hpp"

#include <cmath>
#include <stdexcept>
#include <numbers>

#include "long_double_compare.hpp"
#include "figure_exception.hpp"

namespace Geometry {

namespace {
constexpr std::size_t vertexCount = 4;
}

Trapezoid::Trapezoid() noexcept = default;

Trapezoid::Trapezoid(const Point& start, double angle, double base1, double base2, double side){
    if (base1 <= 0 || base2 <= 0 || side <= 0) {
        throw exceptions::FigureException("Sides must be greater than 0");
    }
    if (compare::AreDoublesEqual(base1, base2)) {
        throw exceptions::FigureException("Bases can't be equal");
    }
    if (side <= std::abs(base1 - base2) / 2) {
        throw exceptions::FigureException("This trapezoid can't exist because of the length of the side length");
    }

    double mathAngle = angle * std::numbers::pi_v<double> / 180;
    double lowerAngle = std::acos(((base1 - base2) / 2) / side);
    double upperAngle = std::numbers::pi - lowerAngle;

    Point firstBase = Point(base1 * std::cos(mathAngle), base1 * std::sin(mathAngle));
    Point secondBase = Point(base2 * std::cos(mathAngle), base2 * std::sin(mathAngle));
    Point sideSide = Point(side * std::cos(mathAngle + upperAngle), side * std::sin(mathAngle + upperAngle));

    points_[0] = start;
    points_[1] = points_[0] + firstBase;
    points_[2] = points_[1] + sideSide;
    points_[3] = points_[2] - secondBase;
}

/// There is no reason to redefine it. 
Trapezoid::Trapezoid(const Trapezoid&) = default;
Trapezoid::Trapezoid(Trapezoid&&) noexcept = default;

// As well as here.
Trapezoid& Trapezoid::operator=(const Trapezoid&) = default;
Trapezoid& Trapezoid::operator=(Trapezoid&&) noexcept = default;

Trapezoid::operator double() const noexcept {
    double base1 = (points_[1] - points_[0]).DistanceToCenter();
    double base2 = (points_[3] - points_[2]).DistanceToCenter();
    double side = (points_[2] - points_[1]).DistanceToCenter();
    double height = std::sqrt(side * side - std::pow((base1 - base2) / 2, 2));
    return (base1 + base2) / 2 * height;
}

Point Trapezoid::Center() const noexcept {
    Point center;
    for (std::size_t i = 0; i < vertexCount; ++i) {
        center += points_[i];
    }
    return 1.0 / vertexCount * center;
}

bool operator==(const Trapezoid& first, const Trapezoid& second) noexcept {
    double base1_1 = (first.points_[0] - first.points_[1]).DistanceToCenter();
    double base2_1 = (first.points_[3] - first.points_[2]).DistanceToCenter();
    double side_1 = (first.points_[2] - first.points_[1]).DistanceToCenter();

    double base1_2 = (second.points_[0] - second.points_[1]).DistanceToCenter();
    double base2_2 = (second.points_[3] - second.points_[2]).DistanceToCenter();
    double side_2 = (second.points_[2] - second.points_[1]).DistanceToCenter();

    if (compare::AreDoublesEqual(base1_1, base1_2)) {
        return compare::AreDoublesEqual(base2_1, base2_2) && compare::AreDoublesEqual(side_1, side_2); 
    }
    return compare::AreDoublesEqual(base1_1, base2_2) && compare::AreDoublesEqual(base2_1, base2_1) && compare::AreDoublesEqual(side_1, side_2);
}

bool operator!=(const Trapezoid& first, const Trapezoid& second) noexcept {
    return !(first == second);
}

void Trapezoid::Print(std::ostream& out) const {
    out << "Trapezoid: ";
    for (std::size_t i = 0; i < vertexCount; ++i) {
        out << points_[i];
    }
}

void Trapezoid::Read(std::istream& in) {
    Point start;
    double angle;
    double base1;
    double base2;
    double side;
    in >> start;
    in >> angle;
    in >> base1;
    in >> base2;
    in >> side;

    *this = Trapezoid(start, angle, base1, base2, side);
}

}