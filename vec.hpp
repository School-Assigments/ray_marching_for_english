#ifndef VEC_HPP
#define VEC_HPP

#include <math.h>

struct vec {
    vec() : x(0), y(0), z(0) {}
    vec(const double& x, const double& y, const double& z) : x(x), y(y), z(z) {}
    vec(const vec& v) : x(v.x), y(v.y), z(v.z) {}

    vec operator=(const vec& v) {
        x = v.x;
        y = v.y;
        z = v.z;
        return *this;
    }

    double x, y, z;
    double& r = x;
    double& g = y;
    double& b = z;
};

vec operator-(const vec& v) {
    return {-v.x, -v.y, -v.z};
}

vec operator+(const vec& lhs, const vec& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

vec operator+(const vec& lhs, const double& rhs) {
    return {lhs.x + rhs, lhs.y + rhs, lhs.z + rhs};
}

vec operator-(const vec& lhs, const vec& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

vec operator*(const vec& lhs, const double& rhs) {
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

vec operator*(const double& lhs, const vec& rhs) {
    return rhs * lhs;
}

vec operator/(const vec& lhs, const double& rhs) {
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

double len(const vec& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double dist(const vec& lhs, const vec& rhs) {
    return len(lhs - rhs);
}

vec normalize(const vec& v) {
    return v / len(v);
}

double dot(const vec& lhs, const vec& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec reflect(const vec& lhs, const vec& rhs) {
    return lhs - 2 * rhs * dot(lhs, rhs);
}

#endif
