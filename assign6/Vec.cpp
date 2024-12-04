#include "Vec.hpp"
#include <cmath>

void Vec::set(double a, double b, double c) {
    this->x = a;
    this->y = b;
    this->z = c;
}

Vec Vec::normalize(Vec ray) {
    //Take the length of the array
    double length = sqrt(ray.x*ray.x + ray.y*ray.y + ray.z*ray.z);

    //Divide each coordinate by the length
    double norm_x = ray.x/length;
    double norm_y = ray.y/length;
    double norm_z = ray.z/length;

    return (Vec) {norm_x, norm_y, norm_z};
}

Vec Vec::add(const Vec &v) {
    return Vec(x + v.x, y + v.y, z + v.z);
}

Vec Vec::operator+ (const Vec &v) {
    return add(v);
}

Vec Vec::sub(const Vec &v) {
    return Vec(x - v.x, y - v.y, z - v.z);
}

Vec Vec::operator- (const Vec &v) {
    return sub(v);
}

Vec Vec::mult(const Vec &v) {
    return Vec(x * v.x, y * v.y, z * v.z);
}

Vec Vec::operator* (const Vec &v) {
    return mult(v);
}

Vec Vec::scalar_mult(const double &c) {
    return Vec(x * c, y * c, z * c);
}

Vec Vec::operator* (const double &c) {
    return scalar_mult(c);
}

Vec Vec::scalar_divide(const double &c) {
    return Vec(x / c, y / c, z / c);
}

Vec Vec::operator/ (const double &c) {
    return scalar_divide(c);
}

int Vec::sum_floor_components(void) {
    return (int) floor(x) + (int) floor(y) + (int) floor(z);
}