#include "Light.hpp"

Light::Light(Vec loc) {
    this->loc = loc;
}

Light::Light() {}

//Determines if the light is blocked by another object
int Light::shadow_test(Vec int_pt, Vec light_loc, Object *cur_obj, Object *objs) {
    Vec shadow_ray = light_loc - int_pt;
    shadow_ray = shadow_ray.normalize();

    for (Object *curr = objs; curr != nullptr; curr = curr->next) {
        if (curr == cur_obj) {
            continue;
        }

        double t;
        Vec dummy_int_pt;
        Vec normal;

        if (curr->intersect((rt) {int_pt, shadow_ray}, &t, &dummy_int_pt, &normal)) {
            if (t > 0.001 && t < (light_loc - int_pt).length()) {
                return 1;
            }
        }
    }
    return 0;
}

//Determines and returns the lighting of the intersected point based on the ray, light location, and object color
Color Light::illuminate(rt ray, Vec int_pt, Object obj, Vec normal, Scene scene) {
    Color color;
    Vec light_loc = this->loc;

    Color obj_color = obj.color;

    if (obj.checker && (int_pt.sum_floor_components() & 1)) {
        obj_color = obj.color2;
    }

    //Ambient lighting
    color.mult_scalar(0.1);

    //Shadow test
    if (shadow_test(int_pt, light_loc, &obj, scene.objs)) {
        return color;
    }

    //Light attenuation
    double dl = (light_loc - int_pt).length();
    double atten = 1/(0.002 * dl * dl + 0.02 * dl + 0.2);

    //Diffuse lighting
    Vec L = light_loc - int_pt;
    L = L.normalize();

    double dp = L.dot(L, normal);
    if (dp <= 0) {
        return color;
    }

    color = color + (obj_color.mult_scalar(dp) * atten);

    //Specular lighting
    Vec R;
    R = L - (normal * 2 * dp);
    R = R.normalize();

    double dp2 = R.dot(R, ray.dir);
    if (dp2 > 0) {
        double specular = pow(dp2, 200) * atten;
        color = color + specular;
    }

    return color;
}
