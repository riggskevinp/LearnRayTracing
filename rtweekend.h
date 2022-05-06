//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_RTWEEKEND_H
#define RAYTRACING_RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

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

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double random_double(double min, double max){
    // Returns a random real in [min,max)
    return min + (max-min)*random_double();
}

constexpr inline double clamp(const double x, const double min, const double max){
    if(x < min){
        return min;
    }
    if(x > max){
        return max;
    }
    return x;
}

// common headers
#include "ray.h"
#include "vec3.h"

#endif //RAYTRACING_RTWEEKEND_H
