//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_HITTABLE_H
#define RAYTRACING_HITTABLE_H

#include "ray.h"

class material;

struct  hit_record {
    point3 p;
    vector3 normal;
    shared_ptr<material> mat_ptr;
    double t{};
    bool front_face{};

    constexpr void set_face_normal(const ray& r, const vector3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    constexpr virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
#endif //RAYTRACING_HITTABLE_H
