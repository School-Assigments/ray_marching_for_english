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

map_val map(const vec& p) {
    static const material red = {{1., 0., 0.}, 0.4, 0.9, 0.1, 100, 0.0};
    static const material mirror = {{1., 1., 1.}, 0.0, 0.3, 1., 50, 0.7};
    const map_val d1 = {sdfbox(p - vec{0., 0., 8.}, {5., 5., 1.}), mirror};
    const map_val d2 = {sdfsphere(p - vec{1., 0., -5.}, 2.), red};
    return min(d1, d2);
}
