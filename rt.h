#include <stdio.h>
#include "vec.h"

//Ray type
typedef struct {
    VP_T origin;
    VP_T dir;
} RAY_T;

//Sphere type
typedef struct {
    VP_T origin;
    double radius;
} SPHERE_T;

//Color type
typedef struct {
    double R;
    double G;
    double B;
} COLOR_T;

//Function prototypes for rt.c
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t, VP_T *int_pt, VP_T *normal);
COLOR_T illuminate(RAY_T ray, VP_T int_pt, COLOR_T obj_color, VP_T normal, VP_T light_loc);
COLOR_T trace(RAY_T ray, SPHERE_T sphere, COLOR_T obj_color, VP_T light_loc);