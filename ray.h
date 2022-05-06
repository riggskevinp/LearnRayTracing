//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"


class ray {
public:
    constexpr ray() = default;
    constexpr ray(const point3& origin, const vector3& direction)
    : orig(origin), dir(direction)
    {}

    [[nodiscard]] constexpr point3 origin() const {return orig;}
    [[nodiscard]] constexpr vector3 direction() const {return dir;}

    [[nodiscard]] constexpr point3 at(double t) const {
        return orig + t*dir;
    }

private:
    point3 orig;
    vector3 dir;
};

#endif //RAYTRACING_RAY_H
