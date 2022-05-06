//
// Created by kr63454 on 5/6/2022.
//

#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere: public hittable {
public:
    constexpr sphere() {}
    constexpr sphere(point3 cen, double r): center(cen), radius(r) {};

    constexpr bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

private:
    point3 center;
    double radius;
};

constexpr bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vector3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if(discriminant < 0){
        return false;
    }
    auto sqrtd = sqrt_helper::sqrt(discriminant);

    // Nearest root that is within range
    auto root = (-half_b - sqrtd) / a;
    if(root < t_min || t_max < root){
        root = (-half_b + sqrtd) / a;
        if(root < t_min || t_max < root){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vector3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}

#endif //RAYTRACING_SPHERE_H