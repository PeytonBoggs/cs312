#ifndef OBJECT_H
#define OBJECT_H

#include "Color.hpp"
#include "rt.hpp"

class Object{
    public:
        Color color;
        Color color2;
        bool checker;

        virtual bool intersect(rt ray, double *t, Vec *int_pt, Vec *normal);

        Object *next;
};


#endif
