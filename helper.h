#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <limits>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline auto degreesToRadians(double degrees) -> double{
    return degrees * pi / 180.0;
}
inline auto randomDouble() -> double {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}
inline auto randomDouble(double min,double max)-> double {
    // Returns a random real in [min,max).
    return min +(max-min)*randomDouble();
}
