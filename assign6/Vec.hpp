#ifndef VEC_H
#define VEC_H
#include <cmath>

class Vec{
        double x;
        double y;
        double z;
    public:
        Vec(double x, double y, double z) : x(x), y(y), z(z) {}
        Vec() {}

        void set(double x, double y, double z);
        Vec normalize(Vec ray);

        double dot(Vec a, Vec b) { return a.x*b.x + a.y*b.y + a.z*b.z; };
        double length(Vec ray) { return sqrt(ray.x*ray.x + ray.y*ray.y + ray.z*ray.z); };

        Vec add(const Vec &v);
        Vec operator+ (const Vec &v);

        Vec sub(const Vec &v);
        Vec operator- (const Vec &v);

        Vec mult(const Vec &v);
        Vec operator* (const Vec &v);

        Vec scalar_mult(const double &c);
        Vec operator* (const double &c);

        Vec scalar_divide(const double &c);
        Vec operator/ (const double &c);

        double sum_components(void) { return x + y + z; };
        double sum_floor_components(void);
};


#endif
