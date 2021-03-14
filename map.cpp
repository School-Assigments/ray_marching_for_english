#include <math.h>
#include <vector>

#include "map.hpp"
#include "vec.hpp"
#include "material.hpp"

using namespace std;

bool operator<(const map_val& lhs, const map_val& rhs) {
    return lhs.d < rhs.d;
}

double sdfsphere(const vec& p, const double& r) {
  return len(p) - r;
}

double sdfbox(const vec& p, const vec& sz) {
    vec q = vec{abs(p.x), abs(p.y), abs(p.z)} - sz;
    return len({max(0., q.x), max(0., q.y), max(0., q.z)}) + min(0., max(q.x, max(q.y, q.z)));
}

double sdfycylinder(const vec& p, const double& r) {
    return hypot(p.x, p.z) - r;
}

double sdfxcylinder(const vec& p, const double& r) {
    return hypot(p.y, p.z) - r;
}

double sdfzcylinder(const vec& p, const double& r) {
    return hypot(p.x, p.y) - r;
}

double unite(const double& d1, const double& d2) {
    return min(d1, d2);
}

double inter(const double& d1, const double& d2) {
    return max(d1, d2);
}

double subst(const double& d1, const double& d2) {
    return max(d1, -d2);
}

double unite(const vector<double>& dist) {
    double d = dist[0];
    for (size_t i = 1; i < dist.size(); ++i) {
        d = unite(d, dist[i]);
    }
    return d;
}

double subst(const double& d1, const vector<double>& dist) {
    return subst(d1, unite(dist));
}

map_val map(const vec& p) {
    static const material red = {{1., 0., 0.}, 0.4, 0.9, 0.1, 100, 0.0};
    static const material mirror = {{1., 1., 1.}, 0.0, 0.3, 1., 50, 0.7};
    // const map_val d1 = {sdfbox(p - vec{0., 0., 8.}, {5., 5., 1.}), mirror};
    double d;
    const double cyl1 = subst(sdfycylinder(p, 1.), {p.y + 1.3, -(p.y - 2.)});
    const double sph1 = sdfsphere(p - vec{0.5, 2.7, 0.3}, 1.3);
    const double box1 = sdfbox(p - vec{-3.5, 0., 1.}, {5., 1., 1.});
    const double cyl2 = subst(sdfycylinder(p - vec{0., 0., -0.5}, 1.), {p.y + 0.3, -(p.y - .1)});
    const double sph2 = sdfsphere(p - vec{0.5, -1.3, -0.5}, 0.7);
    const double cyl3 = subst(sdfzcylinder(p - vec{0., 3.0, 0.3}, 2.), {p.z - 0.2, -(p.z - 0.6)});
    const double cyl4 = subst(sdfxcylinder(p - vec{0., 3.0, 0.3}, 2.), {p.x - 0.2, -(p.x - 0.6)});
    d = subst(unite({subst(sph1, cyl3), box1, cyl2, cyl1}), sph2);
    return min(map_val{d, red}, map_val{cyl4, mirror});
}
