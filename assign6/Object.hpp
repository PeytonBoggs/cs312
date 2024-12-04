#ifndef OBJECT_H
#define OBJECT_H

#include "Color.hpp"
#include "rt.hpp"

class Object{
    public:
        Color color;
        Color color2;
        bool checker;
        Object *next;

        virtual bool intersect(rt ray, double *t, Vec *int_pt, Vec *normal) { return false; };

        Object(Color color, Color color2, bool checker, Object *next) : color(color), color2(color2), checker(checker), next(next) {}
};

#endif
