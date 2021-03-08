#ifndef MAP_HPP
#define MAP_HPP

#include "material.hpp"

struct map_val {
    const double d;
    const material m;
};

bool operator<(const map_val& lhs, const map_val& rhs);

map_val map(const vec& p);

#endif
