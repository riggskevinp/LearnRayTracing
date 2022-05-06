//
// Created by kr63454 on 5/6/2022.
//

#ifndef RAYTRACING_RTWEEKEND_H
#define RAYTRACING_RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include "sqrt_help.h"

// using
using std::shared_ptr;
using std::make_shared;
//using std::sqrt;

// constants
constexpr const double infinity = std::numeric_limits<double>::infinity();
constexpr const double pi = 3.1415926535897932385;

// utility functions
constexpr double degrees_to_radians(double degrees){
    return degrees * pi / 180.0;
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACING_RTWEEKEND_H
