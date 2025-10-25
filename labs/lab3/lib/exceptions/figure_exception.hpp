#pragma once

#include <stdexcept>

namespace exceptions {

class FigureException : public std::logic_error {
    using logic_error::logic_error;
};
}