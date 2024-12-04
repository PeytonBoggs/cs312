#ifndef LIGHT_H
#define LIGHT_H

#include "Vec.hpp"
#include "Color.hpp"
#include "Object.hpp"
#include "scene.hpp"

class Light{
        Vec loc;
        int shadow_test(Vec int_pt, Vec light_loc, Object *cur_obj, Object *objs);
    public:
        explicit Light(Vec loc);
        Light();
        Color illuminate(rt ray, Vec int_pt, Object obj, Vec normal, Scene scene);
};


#endif
