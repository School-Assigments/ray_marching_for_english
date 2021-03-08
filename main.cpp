#include <iostream>
#include <png++/png.hpp>

#include "settings.hpp"
#include "vec.hpp"

using namespace std;

struct material {
    material(const double& a, const double& d,
            const double& s, const double& al, const double& m)
        : ambient(a), diffuse(d), specular(s), alpha(al), mirrow(m) {}
    const double ambient, diffuse, specular, alpha, mirrow;
};
material defaultMaterial(0.4, 0.5, 0.5, 100, 0.7);

double map(const vec& p) {
    double d1 = dist(p, vec(0, 0, 2)) - 1;
    double d2 = dist(p, vec(-2, -0.3, 3)) - 0.5;
    return min(d1, d2);
}

vec calc_normal(const vec& p) {
    static const double eps = 1e-5;
    double d = map(p);
    double nx = map(p + vec(eps, 0, 0)) - d;
    double ny = map(p + vec(0, eps, 0)) - d;
    double nz = map(p + vec(0, 0, eps)) - d;
    return normalize(vec(nx, ny, nz));
}

double marching(const vec& ro, const vec& rd) {
    double t = 0;
    for (int i = 0; i < settings::marching::MAX_ITER; ++i) {
        vec p = ro + t * rd;

        double h = map(p);
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

        vec c = {1., 1., 1.};
        static const vec light_dir = normalize({2, 2, -1});
        material& m = defaultMaterial;
        const double shadow = marching(p + 0.1*norm, light_dir) > settings::marching::ZFAR ? 1. : 0.3;
        c = c * (m.ambient +
                 m.diffuse * dot(norm, light_dir) +
                 m.specular * pow(dot(reflect(light_dir, norm), -rd), m.alpha)) * shadow;
        if (depth < settings::marching::MAX_DEPTH) {
            vec reflect_colour = cast_ray(p + 0.1*norm, reflect(rd, norm), depth + 1);
            c = c * (1 - m.mirrow) + reflect_colour * m.mirrow;
        }
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
