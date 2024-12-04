#include "Plane.hpp"

Plane::Plane(Vec normal, double d, Color color, Color color2, bool checker) : Object(color, color2, checker, nullptr) {
    this->normal = normal;
    this->d = d;
    this->color = color;
    this->color2 = color2;
    this->checker = checker;
}

//Calculates whether a ray intersects with a plane, and calculates values if so. Returns 1 if there is an intersection, and 0 if not.
bool Plane::intersect(rt ray, double *t, Vec *int_pt, Vec *normal) {
    double dp = ray.dir.dot(ray.dir, this->normal);

    if (dp == 0) {
        return false;
    }

    *t = -(ray.origin.dot(ray.origin, this->normal) + this->d) / dp;

    if (*t <= 0) {
        return false;
    }

    *int_pt = (Vec) {ray.origin + (ray.dir.scalar_mult(*t))};

    *normal = this->normal;

    return true;
}