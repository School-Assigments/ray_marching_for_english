#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "vec.hpp"

struct material {
    const vec colour;
    const double ambient, diffuse, specular, alpha, mirrow;
};

#endif
