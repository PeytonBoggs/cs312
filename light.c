#include "light.h"
#include <math.h>

//Determines and returns the lighting of the intersected point based on the ray, light location, and object color
COLOR_T illuminate(RAY_T ray, VP_T int_pt, OBJ_T obj, VP_T normal, SCENE_T scene) {
    COLOR_T color;
    VP_T light_loc = scene.light.loc;

    COLOR_T obj_color = obj.color;
    if (obj.checker && (((int) floor(int_pt.x) + (int) floor(int_pt.y) + (int) floor(int_pt.z)) & 1)) {
        obj_color = obj.color2;
    }

    //Ambient lighting
    color.R = 0.1*obj_color.R;
    color.G = 0.1*obj_color.G;
    color.B = 0.1*obj_color.B;

    //Shadow test
    if (shadow_test(int_pt, light_loc, &obj, scene.objs)) {
        return color;
    }

    //Light attenuation
    double dl = length((VP_T) {light_loc.x - int_pt.x, light_loc.y - int_pt.y, light_loc.z - int_pt.z});
    double atten = 1/(0.002 * dl * dl + 0.02 * dl + 0.2);

    //Diffuse lighting
    VP_T L = {light_loc.x - int_pt.x, light_loc.y - int_pt.y, light_loc.z - int_pt.z};
    L = normalize(L);

    double dp = dot(L, normal);
    if (dp <= 0) {
        return color;
    }

    color.R += dp*obj_color.R * atten;
    color.G += dp*obj_color.G * atten;
    color.B += dp*obj_color.B * atten;

    //Specular lighting
    VP_T R;
    R = (VP_T) {L.x - (normal.x * 2 * dp), L.y - (normal.y * 2 * dp), L.z - (normal.z * 2 * dp)};
    R = normalize(R);

    double dp2 = dot(R, ray.dir);
    if (dp2 > 0) {
        double specular = pow(dp2, 200) * atten;
        color.R += specular;
        color.G += specular;
        color.B += specular;
    }

    return color;
}

//Determines if the light is blocked by another object
static int shadow_test(VP_T int_pt, VP_T light_loc, OBJ_T *cur_obj, OBJ_T *objs) {
    VP_T shadow_ray = {light_loc.x - int_pt.x, light_loc.y - int_pt.y, light_loc.z - int_pt.z};
    shadow_ray = normalize(shadow_ray);

    for (OBJ_T *curr = objs; curr != NULL; curr = curr->next) {
        if (curr == cur_obj) {
            continue;
        }

        double t;
        VP_T dummy_int_pt;
        VP_T normal;

        if (curr->intersect((RAY_T) {int_pt, shadow_ray}, curr, &t, &dummy_int_pt, &normal)) {
            if (t > 0.001 && t < length((VP_T) {light_loc.x - int_pt.x, light_loc.y - int_pt.y, light_loc.z - int_pt.z})) {
                return 1;
            }
        }
    }
    return 0;
}