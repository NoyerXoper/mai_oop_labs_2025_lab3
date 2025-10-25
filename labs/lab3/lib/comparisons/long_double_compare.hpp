#pragma once

#include <cmath>

namespace compare {

namespace {
constexpr double EPS = 1e-12;
}

constexpr bool AreDoublesEqual(double first, double second) {
    if (std::isnan(first) || std::isnan(second)) {
        return false;
    }

    if (std::isinf(first) || std::isinf(second)) {
        return first == second;
    }

    if (first == second) {
        return true;
    }


    double minAbs = std::max(std::min(std::abs(first), std::abs(second)), 1.0);

    return std::abs(second - first) <= EPS * minAbs;
}
}