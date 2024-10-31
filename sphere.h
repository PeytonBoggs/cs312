#ifndef SPHERE_H
#define SPHERE_H

#include "rt.h"

int intersect_sphere(RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal);

#endif