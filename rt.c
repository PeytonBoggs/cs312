#include "rt.h"
#include "light.h"
#include "sphere.h"
#include <stdio.h>
#include <malloc.h>

//Sets the environment and prints a ppm-readable output
int main() {
    FILE *fp = fopen("img.ppm", "w");

    //Header for ppm file
    //FOR P6: fprintf(fp, "P6 1000 1000 255\n");
    fprintf(fp, "P3\n1000 1000\n255\n");

    SCENE_T scene;
    init(&scene);


    //Adding R G B to ppm file for every pixel
    for (int y = 1; y <= 1000; y++) {
        for (int x = 1; x <= 1000; x++) {
            //Calculating ray
            VP_T ray_dir = {((double) x/1000.0) - 0.5, 0.5 - ((double) y/1000.0), 1};
            ray_dir = normalize(ray_dir);
            RAY_T ray = {{0.0, 0.0, 0.0}, ray_dir};

            //Tracing ray
            COLOR_T color = trace(ray, scene);

            //FOR P6: fprintf(fp, "%c%c%c", (unsigned char) color.R, (unsigned char) color.G, (unsigned char) color.B);
            fprintf(fp, "%d %d %d\n", (int) color.R, (int) color.G, (int) color.B);
        }
    }

    fclose(fp);
    return 0;
}

int init(SCENE_T *scene) {
    scene->objs = NULL;
    OBJ_T *node;

    //Sphere 1
    node = (OBJ_T *)malloc(sizeof(OBJ_T));
    node->sphere.origin = (VP_T){-1.0, 0.0, 10.0};
    node->sphere.radius = 2.0;
    node->color = (COLOR_T){1.0, 0.0, 0.0};
    node->intersect = &intersect_sphere;

    //Sphere 2
    node->next = scene->objs;
    scene->objs = node;

    node = (OBJ_T *)malloc(sizeof(OBJ_T));
    node->sphere.origin = (VP_T){1.0, 0.0, 10.0};
    node->sphere.radius = 2.0;
    node->color = (COLOR_T){0.0, 1.0, 0.0};
    node->intersect = &intersect_sphere;

    node->next = scene->objs;
    scene->objs = node;


    scene->light.loc = (VP_T) {5.0, 10.0, 0.0};

    return 0;
}

//Returns color of the pixel based on intersection and illumination
COLOR_T trace(RAY_T ray, SCENE_T scene) {
    COLOR_T color = {0.0, 0.0, 0.0};
    double closest_t;
    VP_T closest_int_pt;
    VP_T closest_normal;
    OBJ_T *closest_obj = NULL;

    //Loop through all objects in the scene to find the closest intersection
    for (OBJ_T *curr = scene.objs; curr != NULL; curr = curr->next) {
        double t;
        VP_T int_pt;
        VP_T normal;

        //If the ray intersects the object, and the intersection is closer than the previous closest intersection, update the closest intersection
        if (curr->intersect(ray, curr, &t, &int_pt, &normal) && (t < closest_t || closest_obj == NULL)) {
            closest_t = t;
            closest_int_pt = int_pt;
            closest_normal = normal;
            closest_obj = curr;
        }
    }

    if (closest_obj == NULL) {
        return color;
    }

    color = illuminate(ray, closest_int_pt, closest_obj->color, closest_normal, scene.light.loc);

    //Cap the lighting so that it does not overflow
    if (color.R > 1) { color.R = 1; }
    if (color.G > 1) { color.G = 1; }
    if (color.B > 1) { color.B = 1; }

    color = (COLOR_T) {color.R * 255, color.G * 255, color.B * 255};

    return color;
}