#include "rt.h"

//Sets the environment and prints a ppm-readable output
int main() {
    //Setting the sphere and light location
    SPHERE_T sphere = {{0.0, 0.0, 10.0}, 2.0};
    COLOR_T obj_color = {1.0, 0.0, 0.0};
    VP_T light_loc = {5.0, 10.0, 0.0};

    //Header for ppm file
    printf("P6 1000 1000 255\n");

    //Adding R G B to ppm file for every pixel
    for (int y = 1; y <= 1000; y++) {
        for (int x = 1; x <= 1000; x++) {
            //Calculating ray
            VP_T ray_dir = {((double) x/1000.0) - 0.5, 0.5 - ((double) y/1000.0), 1};
            ray_dir = normalize(ray_dir);
            RAY_T ray = {{0.0, 0.0, 0.0}, ray_dir};

            //Tracing ray
            COLOR_T color = trace(ray, sphere, obj_color, light_loc);

            printf("%c%c%c", (unsigned char) color.R, (unsigned char) color.G, (unsigned char) color.B);
        }
    }
}

//Calculates whether a ray intersects with a sphere, and calculates values if so. Returns 1 if there is an intersection, and 0 if not.
int intersect_sphere(RAY_T ray, SPHERE_T sphere, double *t, VP_T *int_pt, VP_T *normal) {
    double A, B, C, discriminant;

    //Find intersection based on the quadratic formula
    A = 1;
    B = 2 * (ray.dir.x * (ray.origin.x - sphere.origin.x) + ray.dir.y * (ray.origin.y - sphere.origin.y) + ray.dir.z * (ray.origin.z - sphere.origin.z));
    C = (ray.origin.x - sphere.origin.x)*(ray.origin.x - sphere.origin.x) + (ray.origin.y - sphere.origin.y)*(ray.origin.y - sphere.origin.y) + (ray.origin.z - sphere.origin.z)*(ray.origin.z - sphere.origin.z) - sphere.radius*sphere.radius;

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
    *normal = (VP_T) {int_pt->x - sphere.origin.x, int_pt->y - sphere.origin.y, int_pt->z - sphere.origin.z};
    *normal = normalize(*normal);

    return 1;
}

//Determines and returns the lighting of the intersected point based on the ray, light location, and object color
COLOR_T illuminate(RAY_T ray, VP_T int_pt, COLOR_T obj_color, VP_T normal, VP_T light_loc) {
    COLOR_T color;

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

//Returns color of the pixel based on intersection and illumination
COLOR_T trace(RAY_T ray, SPHERE_T sphere, COLOR_T obj_color, VP_T light_loc) {
    double t;
    VP_T int_pt;
    VP_T normal;
    COLOR_T color = {0.0, 0.0, 0.0};

    //If the ray intersects the sphere, return the illuminated color. Else, return black
    if (intersect_sphere(ray, sphere, &t, &int_pt, &normal)) {
        color = illuminate(ray, int_pt, obj_color, normal, light_loc);
    }

    //Cap the lighting so that it does not overflow
    if (color.R > 1) { color.R = 1; }
    if (color.G > 1) { color.G = 1; }
    if (color.B > 1) { color.B = 1; }

    color = (COLOR_T) {color.R * 255, color.G * 255, color.B * 255};

    return color;
}