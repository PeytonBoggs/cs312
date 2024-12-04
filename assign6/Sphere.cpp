#include "Sphere.hpp"
#include <cmath>

Sphere::Sphere(Vec origin, double radius, Color color, Color color2, bool checker) : Object(color, color2, checker, nullptr) {
    this->origin = origin;
    this->radius = radius;
    this->color = color;
    this->color2 = color2;
    this->checker = checker;
}

//Calculates whether a ray intersects with a sphere, and calculates values if so. Returns 1 if there is an intersection, and 0 if not.
bool Sphere::intersect(rt ray, double *t, Vec *int_pt, Vec *normal) {
    double A, B, C, discriminant;

    //Find intersection based on the quadratic formula
    A = 1;
    B = 2 * ray.dir.dot(ray.dir, (Vec) {ray.origin - this->origin});
    C = (ray.origin - this->origin).dot((ray.origin - this->origin), (ray.origin - this->origin)) - this->radius * this->radius;

    discriminant = (B * B) - (4 * A * C);

    //if there is no intersection, return 0
    if (discriminant <= 0) {
        return false;
    }

    //Find intersections
    double pos_t, neg_t;
    pos_t = (-B + sqrt(discriminant))/(2 * A);
    neg_t = (-B - sqrt(discriminant))/(2 * A);

    //If both intersections are behind us, return 0
    if (pos_t <= 0 || neg_t <= 0) {
        return false;
    }

    //Take the closest intersection in front of us
    *t = (pos_t > neg_t) ? neg_t : pos_t;

    //Calulate the intersection point
    *int_pt = (Vec) {ray.origin + (ray.dir.scalar_mult(*t))};

    //Calculate the normalized normal vector at the intersection point
    *normal = (Vec) {*int_pt - this->origin};
    *normal = (*normal).normalize();

    return true;
}