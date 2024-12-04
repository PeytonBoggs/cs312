#ifndef PLANE_H
#define PLANE_H

#include "Object.hpp"
#include "Vec.hpp"

class Plane: public Object{
    Vec normal;
    double d;

    public:
        Plane(Vec origin, double radius, Color color, Color color2, bool checker);

        bool intersect(rt ray, double *t, Vec *int_pt, Vec *normal) override;
};

#endif
