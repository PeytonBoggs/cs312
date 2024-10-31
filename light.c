#include "light.h"
#include <math.h>

//Determines and returns the lighting of the intersected point based on the ray, light location, and object color
COLOR_T illuminate(RAY_T ray, VP_T int_pt, OBJ_T obj, VP_T normal, VP_T light_loc) {
    COLOR_T color;

    COLOR_T obj_color = obj.color;
    if (obj.checker && (((int) floor(int_pt.x) + (int) floor(int_pt.y) + (int) floor(int_pt.z)) & 1)) {
        obj_color = obj.color2;
    }

    //Ambient lighting
    color.R = 0.1*obj_color.R;
    color.G = 0.1*obj_color.G;
    color.B = 0.1*obj_color.B;

    //Diffuse lighting
    VP_T L = {light_loc.x - int_pt.x, light_loc.y - int_pt.y, light_loc.z - int_pt.z};
    L = normalize(L);

    double dp = dot(L, normal);
    if (dp <= 0) {
        return color;
    }

    color.R += dp*obj_color.R;
    color.G += dp*obj_color.G;
    color.B += dp*obj_color.B;

    //Specular lighting
    VP_T R;
    R = (VP_T) {L.x - (normal.x * 2 * dp), L.y - (normal.y * 2 * dp), L.z - (normal.z * 2 * dp)};
    R = normalize(R);

    double dp2 = dot(R, ray.dir);
    if (dp2 > 0) {
        double specular = pow(dp2, 200);
        color.R += specular;
        color.G += specular;
        color.B += specular;
    }

    return color;
}

static int shadow_test(VP_T int_pt, VP_T light_loc, OBJ_T *cur_obj) {
    //todo
}