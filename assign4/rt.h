#ifndef RT_H
#define RT_H
#define NUM_OBJS 2

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

//Plane type
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

//Scene type
typedef struct {
    OBJ_T *objs;
    LIGHT_T light;
    double start_x;
    double start_y;
    double pixel_size;
} SCENE_T;

//Function prototypes for rt.c
int init(SCENE_T *scene, int num_rows, int num_cols);
COLOR_T trace(RAY_T ray, SCENE_T scene);

#endif