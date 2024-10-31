#include <math.h>

//Vector-point type
typedef struct {
    double x;
    double y;
    double z;
} VP_T;

//Function prototypes for vp.c
VP_T normalize(VP_T ray);
double dot(VP_T x, VP_T y);
double length(VP_T x);