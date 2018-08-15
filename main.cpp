#include <iostream>
#include <fstream>
#include <chrono>
#include "ray.hpp"
#include "hitable.hh"
#include "sphere.hh"
#include "hitable_list.hh"
#include "camera.hh"
#include "material.hh"
#include "lambertian.hh"
#include "metal.hh"

const int width = 600;
const int height = 300;
const int ns = 100;




vec3 color(const ray& r, hitable *world, int depth) {

    hit_record rec;
    if ( world->hit(r, 0.001f, MAXFLOAT, rec) ) {
        ray scattered;
        vec3 attenuation;
        if ( depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0.0f, 0.0f, 0.0f);
        }
    } else {

        vec3 unit_direction = unit_vector(r.direction);
        float t = 0.5f*(unit_direction.y() + 1.0f);
        return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t*vec3(0.5f, 0.7f, 1.0f);
    }
}


int main()
{

    std::ofstream file("image.ppm");
    file << "P3\n" << width << " " << height << "\n255\n";

    camera cam;

    auto start_time = std::chrono::high_resolution_clock::now();

    hitable *list[4];
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambartian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambartian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8, 0.6, 0.2), 1.0f));
    list[3] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8, 0.8, 0.8), 0.3f));

    hitable* world = new hitable_list(list, 4);

    for ( int j = height - 1; j >= 0; j-- ) {
        for ( int i = 0; i < width; i++ ) {
            vec3 col(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < ns; s++) {
                float u = float (i + drand48()) / float (width);
                float v = float (j + drand48()) / float (height);


                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0f);
                col += color(r, world,0);
            }

            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    auto stop_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_time = stop_time - start_time;

    std::cout << "Total rendering time: " << total_time.count() << " s\n";

    file.close();

    return 0;
}