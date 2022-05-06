//
// Created by kr63454 on 5/6/2022.
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

    constexpr double x() const {return e[0];}
    constexpr double y() const {return e[1];}
    constexpr double z() const {return e[2];}

    vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
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

    constexpr double length() const {
        //return std::sqrt(length_squared());
        return sqrt_helper::sqrt(length_squared());
    }

    constexpr double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
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
    return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

constexpr vec3 operator-(const vec3 &u, const vec3 &v){
    return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

constexpr vec3 operator*(const vec3 &u, const vec3 &v){
    return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

constexpr vec3 operator*(double t, const vec3 &v){
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

constexpr vec3 operator*(const vec3 &u, double t){
    return vec3(u.x() * t, u.y() * t, u.z() * t);
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
    return vec3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

constexpr vec3 unit_vector(vec3 v){
    return v / v.length();
}

#endif //RAYTRACING_VEC3_H
