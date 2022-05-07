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


class dielectric: public material {
public:
    constexpr explicit dielectric(double index_of_refraction): ir(index_of_refraction) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vector3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt_helper::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vector3 direction;
        if(cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double()){
            direction = reflect(unit_direction, rec.normal);
        } else {
            direction = refract(unit_direction, rec.normal, refraction_ratio);
        }

        scattered = ray(rec.p, direction);
        return true;
    }

private:
    static double reflectance(double cosine, double ref_idx){
        // Schlick's approximation for reflectance
        auto r0 = (1-ref_idx) / (1+ref_idx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine), 5);
    }
    double ir;
};

#endif //RAYTRACING_MATERIAL_H
