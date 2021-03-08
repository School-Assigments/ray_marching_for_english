#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "vec.hpp"

namespace settings {
    const int IMAGE_WIDTH  = 1920;
    const int IMAGE_HEIGHT = 1280;

    namespace marching {
        const double ZFAR  = 1e2;
        const double ZNEAR = 1;
        const int MAX_ITER = 1e3;
        const double COLL_DIST = 0.0001;
        const int MAX_DEPTH = 5.;
    }

    namespace camera {
        const vec& target = {0., 0., 0.};
        const vec& pos = {-3., 3., -3.};
    }
}

#endif
