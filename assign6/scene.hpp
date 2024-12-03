#ifndef SCENE_H
#define SCENE_H

#include "Light.hpp"
#include "Object.hpp"

class Scene{
    Object *objs;
    Light light;
    double start_x;
    double start_y;
    double pixel_size;
};


#endif
