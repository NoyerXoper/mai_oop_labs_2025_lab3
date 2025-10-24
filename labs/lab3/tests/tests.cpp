#include <gtest/gtest.h>

#include <cmath>

#include "rectangle.hpp"
#include "trapezoid.hpp"
#include "rhombus.hpp"
#include "point.hpp"
#include "figure_exception.hpp"
#include "long_double_compare.hpp"


TEST(PointTests, PointConstructor) {
    ASSERT_NO_THROW ({
        Geometry::Point p1;
        Geometry::Point p2(1.0L, 2.0L);
    });
}

TEST(PointTests, AdditionTest) {
    Geometry::Point p1(1.0L, 1.0L);
    Geometry::Point p2(1.0L, 1.0L);

    Geometry::Point p3 = p1 + p2;

    ASSERT_TRUE(compare::AreDoublesEqual(p3.x, p1.x + p2.x) && compare::AreDoublesEqual(p3.y, p1.y + p2.y));
}

TEST(PointTests, SubtractionTest) {
    Geometry::Point p1(1.0L, 1.0L);
    Geometry::Point p2(1.0L, 1.0L);

    Geometry::Point p3 = p1 - p2;

    ASSERT_TRUE(compare::AreDoublesEqual(p3.x, p1.x - p2.x) && compare::AreDoublesEqual(p3.y, p1.y - p2.y));
}

TEST(PointTests, ScalarMultiplicationTest) {
    Geometry::Point p1(1.0L, 2.0L);
    Geometry::Point p2(6.0L, -3.0L);

    double prod = p1 * p2;

    ASSERT_TRUE(compare::AreDoublesEqual(prod, p1.x * p2.x + p1.y * p2.y));
}

TEST(PointTests, MultiplicationTest) {
    Geometry::Point p1(1.0L, 2.0L);
    double number = 2.0L;
    Geometry::Point expected(p1.x * number, p1.y * number);

    Geometry::Point p = number * p1;

    ASSERT_EQ(p, expected);
}

TEST(PointTests, PointEquals) {
    Geometry::Point p1(1.0L, 1.0L);
    Geometry::Point p2(1.0L, 1.0L);

    Geometry::Point p3 = p1 + p2;

    ASSERT_TRUE(p3 == (p1 + p2));
}

TEST(ConstructorTests, CreateRectangle) {
    ASSERT_NO_THROW ({
        Geometry::Rectangle rect;
        Geometry::Rectangle re(Geometry::Point(4.0L, 4.0L), 0.0L, 12.0L, 10.0L);
    });
}

TEST(ConstructorTests, CreateRhombus) {
    ASSERT_NO_THROW ({
        Geometry::Rhombus rhombus;
        Geometry::Rhombus rh(Geometry::Point(4.0L, 4.0L), 0.0L, 12.0L, 45.0L);
    });
}

TEST(ConstructorTests, CreateTrapezoied) {
    ASSERT_NO_THROW ({
        Geometry::Trapezoid trapezoid;
        Geometry::Trapezoid tr(Geometry::Point(4.0L, 4.0L), 0.0L, 12.0L, 45.0L, 90.0L);
    });
}

TEST(ConstructorTests, CreateBadRectangle) {
    ASSERT_THROW ({
        Geometry::Rectangle re(Geometry::Point(4.0L, 4.0L), 0.0L, -12.0L, 10.0L);
    }, exceptions::FigureException);
}

TEST(ConstructorTests, CreateBadRhombus) {
    ASSERT_THROW ({
        Geometry::Rhombus rh(Geometry::Point(4.0L, 4.0L), 0.0L, -12.0L, 45.0L);
    }, exceptions::FigureException);
}

TEST(ConstructorTests, CreateBadTrapezoied) {
    ASSERT_THROW ({
        Geometry::Trapezoid tr(Geometry::Point(4.0L, 4.0L), 0.0L, -12.0L, 45.0L, 90.0L);
    }, exceptions::FigureException);
}

TEST(CenterTests, RectangleTest) {
    Geometry::Point start;
    double angle = 0;
    double width = 10;
    double height = 11;
    Geometry::Rectangle rect(start, angle, width, height);
    Geometry::Point expected = start + Geometry::Point(width / 2 * std::cos(angle) - height / 2 * std::sin(angle), width / 2 * std::sin(angle) + height / 2 * std::cos(angle));
    ASSERT_EQ(rect.Center(), expected);
}

TEST(CenterTests, RhombusTest) {
    Geometry::Point start;
    double turn = 0;
    double side = 10;
    double angle = 45;
    Geometry::Rhombus rhombus(start, turn, side, angle);
    double mAngle = angle * std::numbers::pi_v<double> / 180;
    double mTurn = turn * std::numbers::pi_v<double> / 180;

    Geometry::Point expected = start + Geometry::Point(side / 2 * (std::cos(mTurn) + std::cos(mAngle + mTurn)), side / 2 * (std::sin(mTurn) + std::sin(mAngle + mTurn)));
    ASSERT_EQ(rhombus.Center(), expected);
}

TEST(CenterTests, TrapezoidTest) {
    Geometry::Point start;
    double angle = 0;
    double base1 = 5;
    double base2 = 10;
    double side = 5;
    double mAngle = angle * std::numbers::pi_v<double> / 180;
    Geometry::Trapezoid trapezoied(start, angle, base1, base2, side);
    double k = std::sqrt(side * side - std::pow((base1 - base2)/2, 2)) / 2;
    Geometry::Point expected = start + Geometry::Point(base1 / 2 * std::cos(mAngle) - k * std::sin(mAngle), base1/2 * std::sin(mAngle) + k * std::cos(mAngle));
    ASSERT_EQ(trapezoied.Center(), expected);
}

TEST(AreaTests, RectangleTest) {
    Geometry::Point start;
    double angle = 0;
    double width = 10;
    double height = 11;
    Geometry::Rectangle rect(start, angle, width, height);
    double expected = width * height;
    ASSERT_TRUE(compare::AreDoublesEqual(static_cast<double>(rect), expected));
}

TEST(AreaTests, RhombusTest) {
    Geometry::Point start;
    double turn = 0;
    double side = 10;
    double angle = 45;
    Geometry::Rhombus rhombus(start, turn, side, angle);
    double mAngle = angle * std::numbers::pi_v<double> / 180;
    double mTurn = turn * std::numbers::pi_v<double> / 180;

    double expected = static_cast<double>(side * side * std::sin(mAngle));
    ASSERT_DOUBLE_EQ(static_cast<double>(rhombus), expected);
}

TEST(AreaTests, TrapezoidTest) {
    Geometry::Point start;
    double angle = 0;
    double base1 = 5;
    double base2 = 10;
    double side = 5;
    double mAngle = angle * std::numbers::pi_v<double> / 180;

    Geometry::Trapezoid trapezoid(start, angle, base1, base2, side);

    double height = std::sqrt(side * side - std::pow((base1 - base2) / 2, 2));
    double expected = height * (base1 + base2) / 2;
    ASSERT_DOUBLE_EQ(static_cast<double>(trapezoid), expected);
}

TEST(EqualsTests, RectangleTest) {
    Geometry::Point starts[4] = {{0, 0}, {12, 13}, {0, 1}, {4, 2}};
    double width = 10;
    double height = 5;
    double turn_deg[4] = {0, 45, 90, 135};
    Geometry::Rectangle rects[4];
    
    for (std::size_t i = 0; i < 4; ++i) {
        rects[i] = Geometry::Rectangle(starts[i], turn_deg[i], width, height);
    }
    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = i; j < 4; ++j) {
            ASSERT_EQ(rects[i], rects[j]);
        }
    }
}

TEST(EqualsTests, RhombusTest) {
    Geometry::Point starts[4] = {{0, 0}, {12, 13}, {0, 1}, {4, 2}};
    double side = 5;
    double angle = 55;
    
    double turn_deg[4] = {0, 45, 90, 135};
    Geometry::Rhombus rhombus[4];
    
    for (std::size_t i = 0; i < 4; ++i) {
        rhombus[i] = Geometry::Rhombus(starts[i], turn_deg[i], side, angle);
    }
    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = i; j < 4; ++j) {
            ASSERT_EQ(rhombus[i], rhombus[j]);
        }
    }
}

TEST(EqualsTests, TrapezoidTest) {
    Geometry::Point starts[4] = {{0, 0}, {12, 13}, {0, 1}, {4, 2}};
    double base1 = 10;
    double base2 = 15;
    double side = 7;
    double turn_deg[4] = {0, 45, 90, 135};
    Geometry::Trapezoid trapezoids[4];
    
    for (std::size_t i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            trapezoids[i] = Geometry::Trapezoid(starts[i], turn_deg[i], base1, base2, side);
        } else {
            trapezoids[i] = Geometry::Trapezoid(starts[i], turn_deg[i], base2, base1, side);
        }
    }
    for (std::size_t i = 0; i < 4; ++i) {
        for (std::size_t j = i; j < 4; ++j) {
            ASSERT_EQ(trapezoids[i], trapezoids[j]);
        }
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}