#ifndef VEC_H
#define VEC_H
#include <cmath>

class Vec{
        double x;
        double y;
        double z;
    public:
        Vec(double a, double b, double c) : x(a), y(b), z(c) {}
        Vec() = default;

        void set(double a, double b, double c);
        Vec normalize();

        double dot(Vec a, Vec b) { return a.x*b.x + a.y*b.y + a.z*b.z; };
        double length() { return sqrt(x*x + y*y + z*z); };

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
        int sum_floor_components(void);
};


#endif
