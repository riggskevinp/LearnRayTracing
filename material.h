//
// Created on 5/7/2022.
//

#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "rtweekend.h"

struct hit_record;

class material {
public:
    constexpr virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const = 0;
};


class lambertian: public material{
public:
    constexpr explicit lambertian(const color& a): albedo(a) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        (void)r_in;
        auto scatter_direction = rec.normal + random_in_hemisphere(rec.normal);
        // Three options for diffuse materials
        //point3 target = rec.p + rec.normal + random_in_hemisphere(rec.normal);
        //point3 target = rec.p + rec.normal + random_unit_vector();
        //point3 target = rec.p + rec.normal + random_in_unit_sphere();

        // Catch degenerate scatter direction
        // if scatter is too close to zero, normal and scatter sum to zero resulting in infinities and NaNs.
        if(scatter_direction.near_zero()){
            scatter_direction = rec.normal;
        }

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};


class metal: public material {
public:
    constexpr explicit metal(const color& a, double f): albedo(a), fuzz(f < 1 ? f : 1) {}

    constexpr bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        vector3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz* random_in_hemisphere(rec.normal));
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    color albedo;
    double fuzz;
};

#endif //RAYTRACING_MATERIAL_H
