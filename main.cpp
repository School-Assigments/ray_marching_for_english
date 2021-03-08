#include <iostream>
#include <png++/png.hpp>

#include "settings.hpp"
#include "vec.hpp"

using namespace std;

struct material {
    const vec colour;
    const double ambient, diffuse, specular, alpha, mirrow;
};

struct map_val {
    const double d;
    const material m;
};

bool operator<(const map_val& lhs, const map_val& rhs) {
    return lhs.d < rhs.d;
}

map_val map(const vec& p) {
    map_val d1 = {dist(p, vec(0, 0, 2)) - 1,
                  {{1., 0., 0.}, 0.4, 0.9, 0.1, 100, 0.0}};
    map_val d2 = {dist(p, vec(-2, -0.3, 3)) - 0.5,
                  {{1., 1., 1.}, 0.0, 0.3, 1., 50, 0.7}};
    return min(d1, d2);
}

vec calc_normal(const vec& p) {
    static const double eps = 1e-5;
    double d = map(p).d;
    double nx = map(p + vec(eps, 0, 0)).d - d;
    double ny = map(p + vec(0, eps, 0)).d - d;
    double nz = map(p + vec(0, 0, eps)).d - d;
    return normalize(vec(nx, ny, nz));
}

double marching(const vec& ro, const vec& rd) {
    double t = 0;
    for (int i = 0; i < settings::marching::MAX_ITER; ++i) {
        vec p = ro + t * rd;

        double h = map(p).d;
        if (abs(h) < settings::marching::COLL_DIST ||
            t > settings::marching::ZFAR) {
            break;
        }
        t += h;
    }
    return t;
}

vec cast_ray(const vec& ro, const vec& rd, const int depth = 0) {
    double t = marching(ro, rd);
    if (t < settings::marching::ZFAR) {
        vec p = ro + rd * t;
        vec norm = calc_normal(p);

        static const vec light_dir = normalize({2, 2, -1});

        const material m = map(p).m;
        const double shadow = marching(p + 0.0001*norm, light_dir) > settings::marching::ZFAR ? 1. : 0.3;
        vec c = m.colour;
        vec reflect_colour = {0, 0, 0};
        if (m.mirrow > 0 && depth < settings::marching::MAX_DEPTH) {
            reflect_colour = cast_ray(p + 0.0001*norm, reflect(rd, norm), depth + 1);
        }
        c = c * (m.ambient +
                 shadow * m.diffuse * dot(norm, light_dir)) +
            shadow * m.specular * pow(dot(reflect(light_dir, norm), -rd), m.alpha) +
            reflect_colour * m.mirrow;
        return c;
    }
    return {0., 1., 1.};
}

int main() {
    png::image<png::rgb_pixel> canvas(settings::IMAGE_WIDTH, settings::IMAGE_HEIGHT);
    for (int x = 0; x < settings::IMAGE_WIDTH; ++x) {
        for (int y = 0; y < settings::IMAGE_HEIGHT; ++y) {
            static const int MIN_RES = min(settings::IMAGE_WIDTH, settings::IMAGE_HEIGHT);
            double u = (x -  settings::IMAGE_WIDTH/2.) / (MIN_RES/2.);
            double v = (y - settings::IMAGE_HEIGHT/2.) / (MIN_RES/2.);

            vec ro = {0, 0, 0};
            vec rd = normalize({u, -v, settings::marching::ZNEAR});

            vec c = cast_ray(ro, rd);
            canvas.set_pixel(x, y, png::rgb_pixel(max(0., min(1., c.x)) * 255,
                                                  max(0., min(1., c.y)) * 255,
                                                  max(0., min(1., c.z)) * 255));
        }
    }
    canvas.write("output.png");
}
