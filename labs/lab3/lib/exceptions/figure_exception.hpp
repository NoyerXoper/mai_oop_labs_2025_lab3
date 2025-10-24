#pragma once

#include <stdexcept>

namespace exceptions {

class FigureException : public std::invalid_argument {
    using invalid_argument::invalid_argument;
};
}