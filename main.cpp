#include <iostream>
#include <fstream>
#include "ray.hpp"
#include "hitable.hh"
#include "sphere.hh"
#include "hitable_list.hh"

const int width = 600;
const int height = 300;



vec3 color(const ray& r, hitable *world) {

    hit_record rec;
    if ( world->hit(r, 0.0f, MAXFLOAT, rec) ) {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() +1);
    }

    vec3 unit_direction = unit_vector(r.direction);
    float t = 0.5f * (unit_direction.y() + 1.0f);
    return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}


int main()
{

    std::ofstream file("image.ppm");
    file << "P3\n" << width << " " << height << "\n255\n";

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    hitable *list[2];
    list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);

    hitable* world = new hitable_list(list, 2);

    for ( int j = height - 1; j >= 0; j-- ) {
        for ( int i = 0; i < width; i++ ) {

            float u = float (i) / float (width);
            float v = float (j) / float (height);

            ray r(origin, lower_left_corner + u*horizontal + v*vertical);

            vec3 p = r.point_at_parameter(2.0f);
            vec3 col = color(r, world);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    file.close();

    return 0;
}