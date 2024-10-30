#ifndef RT_H
#define RT_H

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

typedef struct {
    VP_T normal;
    double d;
} PLANE_T;

//Color type
typedef struct {
    double R;
    double G;
    double B;
} COLOR_T;

//Light type
typedef struct {
    VP_T loc;
} LIGHT_T;

//Object type
typedef struct OBJ {
    union {
        SPHERE_T sphere;
        PLANE_T plane;
    };
    char type;
    COLOR_T color;
    COLOR_T color2;
    int checker;
    int (*intersect)(RAY_T ray, struct OBJ *obj, double *t, VP_T *int_pt, VP_T *normal);
    struct OBJ *next;
} OBJ_T;

//Function prototypes for rt.c
COLOR_T trace(RAY_T ray, SPHERE_T sphere, COLOR_T obj_color, VP_T light_loc);

#endif