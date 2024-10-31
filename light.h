#ifndef LIGHT_H
#define LIGHT_H

#include "rt.h"

COLOR_T illuminate(RAY_T ray, VP_T int_pt, OBJ_T obj, VP_T normal, VP_T light_loc);
static int shadow_test(VP_T int_pt, VP_T light_loc, OBJ_T *cur_obj);

#endif // LIGHT_H