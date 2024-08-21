#ifndef VEC3_H
#define VEC3_H

#include "rtweekend.h"
#include "color.h"

class vec3 {
public:
    double e[3];

    vec3() : e{0, 0, 0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        if (t != 0) {
            return *this *= 1 / t;
        }
        // Handle division by zero as needed
        return *this;
    }

    double length() const {
        return std::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    static vec3 random() {
        return vec3 (random_double(), random_double(), random_double());
    }

    static vec3 random(double min, double max) {
        return vec3 (random_double(min, max), random_double(min, max), random_double(min, max));
    }

    vec3 normalize() const{
        double len = length();
        if(len != 0){
            return vec3(e[0]/len,e[1]/len,e[2]/len);
        }
            throw std::runtime_error("Cannot normalize zero-length vector");
    }
};

// point3 is an alias for vec3, useful for geometric clarity.
using point3 = vec3;

// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    if (t != 0) {
        return (1 / t) * v;
    }
    // Handle division by zero as needed
    return vec3();
}

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

inline vec3 randomInUnitSphere() {
    while (true){
        auto p = vec3::random(-1,1);
        if (p.length_squared() < 1)
            return p;
    }
}

inline vec3 randomUnitVector() {
    return unit_vector(randomInUnitSphere());
}

inline vec3 randomOnHemisphere(const vec3& normal) {
    vec3 onUnitSphere = randomUnitVector();
    if(dot(onUnitSphere, normal) > 0.0) // in same hemisphere as normal
        return onUnitSphere;
    else{
        return -onUnitSphere;
    }
}

#endif
