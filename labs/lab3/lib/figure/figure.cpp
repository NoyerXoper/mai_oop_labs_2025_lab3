#include "figure.hpp"

namespace Geometry {

Figure::~Figure() noexcept=default;

std::ostream& operator<<(std::ostream& out, const Figure& fig) {
    fig.Print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Figure& fig) {
    fig.Read(in);
    return in;
}
}