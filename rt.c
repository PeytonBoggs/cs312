#include "rt.h"
#include "light.h"
#include "sphere.h"
#include <stdio.h>

//Sets the environment and prints a ppm-readable output
int main() {
    //Setting the sphere and light location
    SPHERE_T sphere = {{0.0, 0.0, 10.0}, 2.0};
    COLOR_T obj_color = {1.0, 0.0, 0.0};
    LIGHT_T light = {5.0, 10.0, 0.0};

    FILE *fp = fopen("img.ppm", "w");

    //Header for ppm file
    //FOR P6: fprintf(fp, "P6 1000 1000 255\n");
    fprintf(fp, "P3\n1000 1000\n255\n");

    SPHERE_T *list = NULL;


    //Adding R G B to ppm file for every pixel
    for (int y = 1; y <= 1000; y++) {
        for (int x = 1; x <= 1000; x++) {
            //Calculating ray
            VP_T ray_dir = {((double) x/1000.0) - 0.5, 0.5 - ((double) y/1000.0), 1};
            ray_dir = normalize(ray_dir);
            RAY_T ray = {{0.0, 0.0, 0.0}, ray_dir};

            //Tracing ray
            COLOR_T color = trace(ray, sphere, obj_color, light.loc);

            //FOR P6: fprintf(fp, "%c%c%c", (unsigned char) color.R, (unsigned char) color.G, (unsigned char) color.B);
            fprintf(fp, "%d %d %d\n", (int) color.R, (int) color.G, (int) color.B);
        }
    }

    fclose(fp);
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