#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace settings {
    const int IMAGE_WIDTH  = 800;
    const int IMAGE_HEIGHT = 600;

    namespace marching {
        const double ZFAR  = 1e2;
        const double ZNEAR = 1;
        const int MAX_ITER = 1e3;
        const double COLL_DIST = 0.0001;
        const int MAX_DEPTH = 5.;
    }
}

#endif
