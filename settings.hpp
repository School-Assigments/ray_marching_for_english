#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "vec.hpp"

namespace settings {
    const int IMAGE_WIDTH  = 300;
    const int IMAGE_HEIGHT = 300;

    namespace marching {
        const double ZFAR  = 20;
        const double ZNEAR = 1.;
        const int MAX_ITER = 1e4;
        const double COLL_DIST = 1e-5;
        const int MAX_DEPTH = 5.;
    }

    namespace camera {
        const vec& target = {0., 0., 0.};
        const vec& pos = {2.5, -2.0, -1.5};
    }
}

#endif
