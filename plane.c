#include "plane.h"

//Calculates whether a ray intersects with a plane, and calculates values if so. Returns 1 if there is an intersection, and 0 if not.
int intersect_plane(RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal) {
    double dp = dot(ray.dir, obj->plane.normal);

    if (dp == 0) {
        return 0;
    }

    *t = -(dot(ray.origin, obj->plane.normal) + obj->plane.d) / dp;

    if (*t <= 0) {
        return 0;
    }

    *int_pt = (VP_T) {ray.origin.x + (*t * ray.dir.x), ray.origin.y + (*t * ray.dir.y), ray.origin.z + (*t * ray.dir.z)};

    *normal = obj->plane.normal;

    return 1;
}