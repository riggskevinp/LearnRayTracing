//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "rtweekend.h"

class Camera {
public:
    Camera(point3 lookfrom, point3 lookat, vector3 vup,
           double vfov, double aspect_ratio, double aperture, double focus_distance) {
        // vfov is vertical field-of-view in degrees
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_distance*w;
        lens_radius = aperture / 2;
    }

    [[nodiscard]] constexpr ray get_ray(double s, double t) const {
        vector3 rd = lens_radius * random_in_unit_disk();
        vector3 offset = u * rd.x() + v * rd.y();

        return {origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset};
    }
private:
    point3 origin;
    point3 lower_left_corner;
    vector3 horizontal;
    vector3 vertical;
    vector3 u, v, w;
    double lens_radius;
};

#endif //RAYTRACING_CAMERA_H
