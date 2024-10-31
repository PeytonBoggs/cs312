#ifndef PLANE_H
#define PLANE_H

#include "rt.h"

int intersect_plane(RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal);

#endif