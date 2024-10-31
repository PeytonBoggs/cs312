#include "rt.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include <stdio.h>
#include <malloc.h>

//Sets the environment and prints a ppm-readable output
int main() {
    //Screen size
    int screen_height = 1080;
    int screen_width = 1920;

    //Initializes the scene
    SCENE_T scene;
    init(&scene, screen_height, screen_width);

    FILE *fp = fopen("img.ppm", "w");

    //Header for ppm file
    //FOR P6: fprintf(fp, "P6 1000 1000 255\n");
    fprintf(fp, "P3\n%d %d\n255\n", screen_width, screen_height);

    //Adding R G B to ppm file for every pixel
    for (int y = 1; y <= screen_height; y++) {
        for (int x = 1; x <= screen_width; x++) {
            //Calculating ray
            VP_T ray_dir = { x * scene.pixel_size + scene.start_x, scene.start_y - y * scene.pixel_size, 1};
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

//Initializes the scene with objects and light
int init(SCENE_T *scene, int num_rows, int num_cols) {
    int height = 1;
    int width = num_cols/num_rows;

    scene->pixel_size = 1.0 / num_rows;
    scene->start_y = 0.5;
    scene->start_x = -((double) num_cols / num_rows) / 2.0;

    FILE *fp = fopen("scene1.txt", "r");

    char c;
    scene->objs = NULL;
    OBJ_T *node;

    //Read the scene file
    while (fscanf(fp, "%c", &c) != EOF) {
        if (c == 's') {
            node = (OBJ_T *)malloc(sizeof(OBJ_T));
            fscanf(fp, "%lf %lf %lf", &node->sphere.origin.x, &node->sphere.origin.y, &node->sphere.origin.z);
            fscanf(fp, "%lf", &node->sphere.radius);
            fscanf(fp, "%lf %lf %lf", &node->color.R, &node->color.G, &node->color.B);
            node->intersect = &intersect_sphere;
            node->next = scene->objs;
            scene->objs = node;
            node->checker = 0;
        } else if (c == 'p') {
            node = (OBJ_T *)malloc(sizeof(OBJ_T));
            fscanf(fp, "%lf %lf %lf", &node->plane.normal.x, &node->plane.normal.y, &node->plane.normal.z);
            fscanf(fp, "%lf", &node->plane.d);
            fscanf(fp, "%lf %lf %lf", &node->color.R, &node->color.G, &node->color.B);
            fscanf(fp, "%lf %lf %lf", &node->color2.R, &node->color2.G, &node->color2.B);
            node->intersect = &intersect_plane;
            node->checker = 1;
            node->next = scene->objs;
            scene->objs = node;
        } else if (c == 'l') {
            fscanf(fp, "%lf %lf %lf", &scene->light.loc.x, &scene->light.loc.y, &scene->light.loc.z);
        }
    }

    return 0;
}

//Returns color of the pixel based on intersection and illumination
COLOR_T trace(RAY_T ray, SCENE_T scene) {
    COLOR_T color = {76.5, 76.5, 127.5};
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

    color = illuminate(ray, closest_int_pt, *closest_obj, closest_normal, scene);

    //Cap the lighting so that it does not overflow
    if (color.R > 1) { color.R = 1; }
    if (color.G > 1) { color.G = 1; }
    if (color.B > 1) { color.B = 1; }

    color = (COLOR_T) {color.R * 255, color.G * 255, color.B * 255};

    return color;
}