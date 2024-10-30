#include "vec.h"

//Normalizes and returns a ray
VP_T normalize(VP_T ray) {
    //Take the length of the array
    double length = sqrt(ray.x*ray.x + ray.y*ray.y + ray.z*ray.z);

    //Divide each coordinate by the length
    double norm_x = ray.x/length;
    double norm_y = ray.y/length;
    double norm_z = ray.z/length;

    return (VP_T) {norm_x, norm_y, norm_z};
}

//Returns the dot product of two vectors
double dot(VP_T a, VP_T b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}