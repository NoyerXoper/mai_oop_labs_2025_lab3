#pragma once

#include <stdexcept>

namespace exceptions {

class ArrayOutOfRange : public std::range_error {
    using range_error::range_error;
};
}