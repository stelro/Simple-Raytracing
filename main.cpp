#include <iostream>
#include <fstream>
#include "ray.hpp"
#include "hitable.hh"
#include "sphere.hh"
#include "hitable_list.hh"
#include "camera.hh"

const int width = 600;
const int height = 300;
const int ns = 100;

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        /// room for more optimazaitons here
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1.0f,1.0f, 1.0f);
    } while ( p.squared_length() >= 1.0f );

    return p;
}


vec3 color(const ray& r, hitable *world) {

    hit_record rec;
    if ( world->hit(r, 0.001f, MAXFLOAT, rec) ) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5f * color( ray(rec.p, target-rec.p), world);
    }

    vec3 unit_direction = unit_vector(r.direction);
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}


int main()
{

    std::ofstream file("image.ppm");
    file << "P3\n" << width << " " << height << "\n255\n";

    camera cam;

    hitable *list[2];
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);

    hitable* world = new hitable_list(list, 2);

    for ( int j = height - 1; j >= 0; j-- ) {
        for ( int i = 0; i < width; i++ ) {
            vec3 col(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < ns; s++) {
                float u = float (i + drand48()) / float (width);
                float v = float (j + drand48()) / float (height);


                ray r = cam.get_ray(u,v);
                vec3 p = r.point_at_parameter(2.0f);
                col += color(r, world);
            }

            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    file.close();

    return 0;
}