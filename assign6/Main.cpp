#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Color.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"
#include "scene.hpp"
#include "Light.hpp"

int init(Scene *scene, Light *light, int num_rows, int num_cols);
Color trace(rt ray, Scene scene, Light light);

//Sets the environment and prints a ppm-readable output
int main() {
    //Screen size
    int screen_height = 480;
    int screen_width = 640;

    //Initializes the scene
    Scene scene{};
    Light light{};
    init(&scene, &light, screen_height, screen_width);

    //Opening ppm file
    ofstream file("img.ppm", std::ios::binary);

    //Header for ppm file
    file << "P6\n" << screen_width << " " << screen_height << "\n255\n";

    //Adding R G B to ppm file for every pixel
    for (int y = 1; y <= screen_height; y++) {
        for (int x = 1; x <= screen_width; x++) {
            //Calculating ray
            Vec ray_dir = { x * scene.pixel_size + scene.start_x, scene.start_y - y * scene.pixel_size, 1};
            ray_dir = ray_dir.normalize();
            rt ray = {{0.0, 0.0, 0.0}, ray_dir};

            //Tracing ray
            Color color = trace(ray, scene, light);

            //Adding color to ppm file
            file.put(static_cast<char>(color.getR()));
            file.put(static_cast<char>(color.getG()));
            file.put(static_cast<char>(color.getB()));
        }
    }

    file.close();

    return 0;
}

//Initializes the scene with objects and light
int init(Scene *scene, Light *light, int num_rows, int num_cols) {
    int height = 1;
    int width = num_cols/num_rows;

    scene->pixel_size = 1.0 / num_rows;
    scene->start_y = 0.5;
    scene->start_x = -((double) num_cols / num_rows) / 2.0;

    ifstream file;
    file.open("scene1.txt");

    stringstream ss;
    char c;
    scene->objs = nullptr;

    //Read the scene file
    string line;
    while (getline(file, line)) {
        c = line[0];
        if (c == 's') {
            double origin_x, origin_y, origin_z, radius, r, g, b;

            //First Line - Origin
            getline(file, line);
            ss = stringstream(line);
            ss >> origin_x >> origin_y >> origin_z;

            //Second Line - Radius
            getline(file, line);
            ss = stringstream (line);
            ss >> radius;

            //Third Line - Color
            getline(file, line);
            ss = stringstream (line);
            ss >> r >> g >> b;

            //Create sphere object
            Object *sphere = new Sphere({origin_x, origin_y, origin_z}, radius, {r, g, b}, {0, 0, 0}, false);

            sphere->next = scene->objs;
            scene->objs = sphere;
        } else if (c == 'p') {
            double normal_x, normal_y, normal_z, d, r1, g1 ,b1, r2, g2, b2;

            //First Line - Normal
            getline(file, line);
            ss = stringstream(line);
            ss >> normal_x >> normal_y >> normal_z;

            //Second Line - d
            getline(file, line);
            ss = stringstream (line);
            ss >> d;

            //Third Line - Color 1
            getline(file, line);
            ss = stringstream (line);
            ss >> r1 >> g1 >> b1;

            //Fourth Line - Color 2
            getline(file, line);
            ss = stringstream (line);
            ss >> r2 >> g2 >> b2;

            //Create plane object
            Object *plane = new Plane({normal_x, normal_y, normal_z}, d, {r1, g1, b1}, {r2, g2, b2}, true);

            plane->next = scene->objs;
            scene->objs = plane;
        } else if (c == 'l') {
            double loc_x, loc_y, loc_z;

            //First Line - Light Location
            getline(file, line);
            ss = stringstream (line);
            ss >> loc_x >> loc_y >> loc_z;

            *light = Light({loc_x, loc_y, loc_z});
        }
    }

    file.close();

    return 0;
}

//Returns color of the pixel based on intersection and illumination
Color trace(rt ray, Scene scene, Light light) {
    Color color = {76.5, 76.5, 127.5};
    double closest_t;
    Vec closest_int_pt{};
    Vec closest_normal{};
    Object *closest_obj = nullptr;

    //Loop through all objects in the scene to find the closest intersection
    for (Object *curr = scene.objs; curr != nullptr; curr = curr->next) {
        double t;
        Vec int_pt{};
        Vec normal{};

        //If the ray intersects the object, and the intersection is closer than the previous closest intersection, update the closest intersection
        if (curr->intersect(ray, &t, &int_pt, &normal) && (t < closest_t || closest_obj == nullptr)) {
            closest_t = t;
            closest_int_pt = int_pt;
            closest_normal = normal;
            closest_obj = curr;
        }
    }

    if (closest_obj == nullptr) {
        return color;
    }

    color = light.illuminate(ray, closest_int_pt, *closest_obj, closest_normal, scene);

    color.cap();
    color = color.mult_scalar(255);

    return color;
}