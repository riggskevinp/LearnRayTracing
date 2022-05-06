//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "rtweekend.h"

class Camera {
public:
    constexpr Camera() {
        constexpr auto aspect_ratio = 16.0 / 9.0;
        constexpr auto viewport_height = 2.0;
        constexpr auto viewport_width = aspect_ratio * viewport_height;
        constexpr auto focal_length = 1.0;

        origin = point3(0,0,0);
        horizontal = vector3(viewport_width, 0.0, 0.0);
        vertical = vector3(0.0, viewport_height, 0.0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vector3(0, 0, focal_length);
    }

    [[nodiscard]] constexpr ray get_ray(double u, double v) const {
        return {origin, lower_left_corner + u*horizontal + v*vertical - origin};
    }
private:
    point3 origin;
    point3 lower_left_corner;
    vector3 horizontal;
    vector3 vertical;
};

#endif //RAYTRACING_CAMERA_H
