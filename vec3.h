//
// Created on 5/6/2022.
//

#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <cmath>
#include <iostream>

//#include <Eigen/Dense>

#include "sqrt_help.h"

class vec3 {
public:
    constexpr vec3(): e{0,0,0} {}
    constexpr vec3(double e0, double e1, double e2): e{e0,e1,e2} {}

    [[nodiscard]] constexpr double x() const {return e[0];}
    [[nodiscard]] constexpr double y() const {return e[1];}
    [[nodiscard]] constexpr double z() const {return e[2];}

    vec3 operator-() const {return {-e[0], -e[1], -e[2]};}
    constexpr double operator[](int i) const {return e[i];}
    constexpr double& operator[](int i) {return e[i];}

    constexpr vec3& operator+=(const vec3 &v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    constexpr vec3& operator*=(const double t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    constexpr vec3& operator/=(const double t){
        return *this *= 1/t;
    }

    [[nodiscard]] constexpr double length() const {
        //return std::sqrt(length_squared());
        return sqrt_helper::sqrt(length_squared());
    }

    [[nodiscard]] constexpr double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    static inline vec3 random() {
        return {random_double(),random_double(),random_double()};
    }

    static inline vec3 random(double min, double max){
        return {random_double(min, max), random_double(min, max), random_double(min,max)};
    }

    [[nodiscard]] bool near_zero() const {
        // Return true if the vector is close to zero in all dimensions
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

private:
    double e[3];

};

using point3 = vec3;
using color = vec3;
using vector3 = vec3;

// eigen not constexpr
/*
using point3 = Eigen::Vector3d;
using color = Eigen::Vector3d;
using vector3 = Eigen::Vector3d;
*/

// Utilities
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

constexpr vec3 operator+(const vec3 &u, const vec3 &v){
    return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

constexpr vec3 operator-(const vec3 &u, const vec3 &v){
    return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};
}

constexpr vec3 operator*(const vec3 &u, const vec3 &v){
    return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

constexpr vec3 operator*(double t, const vec3 &v){
    return {t * v.x(), t * v.y(), t * v.z()};
}

constexpr vec3 operator*(const vec3 &u, double t){
    return {u.x() * t, u.y() * t, u.z() * t};
}

constexpr vec3 operator/(const vec3 &u, double t){
    return (1/t) * u;
}

constexpr double dot(const vec3 &u, const vec3 &v){
    return u.x() * v.x()
    + u.y() * v.y()
    + u.z() * v.z();
}

constexpr vec3 cross(const vec3 &u, const vec3 &v){
    return {u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x()};
}

constexpr vec3 unit_vector(vec3 v){
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    while(true) {
        auto p = vec3::random(-1,1);
        if(p.length_squared() >= 1){
            continue;
        }
        return p;
    }
}

vec3 random_unit_vector(){
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal){
    vec3 in_unit_sphere = random_in_unit_sphere();
    if(dot(in_unit_sphere, normal) > 0.0){
        return in_unit_sphere;
    } else {
        return -in_unit_sphere;
    }
}

constexpr vec3 reflect(const vec3& v, const vec3& n){
    /*
     * Reflection, ie metals.
     * equation is v + 2b
     * surface normal dotted with v gives the length of b
     * v points in the opposite direction so we need to negate it
     */
    return v - 2*dot(v,n)*n;
}

#endif //RAYTRACING_VEC3_H
