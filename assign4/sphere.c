#include "sphere.h"

//Calculates whether a ray intersects with a sphere, and calculates values if so. Returns 1 if there is an intersection, and 0 if not.
int intersect_sphere(RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal) {
    double A, B, C, discriminant;

    //Find intersection based on the quadratic formula
    A = 1;
    B = 2 * (ray.dir.x * (ray.origin.x - obj->sphere.origin.x) + ray.dir.y * (ray.origin.y - obj->sphere.origin.y) + ray.dir.z * (ray.origin.z - obj->sphere.origin.z));
    C = (ray.origin.x - obj->sphere.origin.x)*(ray.origin.x - obj->sphere.origin.x) + (ray.origin.y - obj->sphere.origin.y)*(ray.origin.y - obj->sphere.origin.y) + (ray.origin.z - obj->sphere.origin.z)*(ray.origin.z - obj->sphere.origin.z) - obj->sphere.radius*obj->sphere.radius;

    discriminant = (B * B) - (4 * A * C);

    //if there is no intersection, return 0
    if (discriminant <= 0) {
        return 0;
    }

    //Find intersections
    double pos_t, neg_t;
    pos_t = (-B + sqrt(discriminant))/(2 * A);
    neg_t = (-B - sqrt(discriminant))/(2 * A);

    //If both intersections are behind us, return 0
    if (pos_t <= 0 || neg_t <= 0) {
        return 0;
    }

    //Take the closest intersection in front of us
    *t = (pos_t > neg_t) ? neg_t : pos_t;

    //Calulate the intersection point
    *int_pt = (VP_T) {(ray.origin.x + (*t * ray.dir.x)), (ray.origin.y + (*t * ray.dir.y)), (ray.origin.z + (*t * ray.dir.z))};

    //Calculate the normalized normal vector at the intersection point
    *normal = (VP_T) {int_pt->x - obj->sphere.origin.x, int_pt->y - obj->sphere.origin.y, int_pt->z - obj->sphere.origin.z};
    *normal = normalize(*normal);

    return 1;
}