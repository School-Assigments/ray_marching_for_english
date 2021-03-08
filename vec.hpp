#ifndef VEC_HPP
#define VEC_HPP

#include <math.h>

struct vec {
    vec();
    vec(const double& x, const double& y, const double& z);
    vec(const vec& v);

    vec operator=(const vec& v);

    double x, y, z;
    double& r = x;
    double& g = y;
    double& b = z;
};

vec operator-(const vec& v);
vec operator+(const vec& lhs, const vec& rhs);
vec operator+(const vec& lhs, const double& rhs);
vec operator-(const vec& lhs, const vec& rhs);
vec operator*(const vec& lhs, const double& rhs);
vec operator*(const double& lhs, const vec& rhs);
vec operator/(const vec& lhs, const double& rhs);

double len(const vec& v);
double dist(const vec& lhs, const vec& rhs);
double dot(const vec& lhs, const vec& rhs);

vec normalize(const vec& v);
vec reflect(const vec& lhs, const vec& rhs);

#endif
