#ifndef SPHERE_H
#define SPHERE_H

#include "Object.hpp"
#include "Vec.hpp"

class Sphere: public Object{
        Vec origin;
        double radius;

    public:
        Sphere(Vec origin, double radius, Color color, Color color2, bool checker);

        bool intersect(rt ray, double *t, Vec *int_pt, Vec *normal);
};


#endif
