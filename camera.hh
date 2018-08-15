//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_CAMERA_HH
#define OFFTRACER_CAMERA_HH

#include "vec3.hpp"
#include "ray.hpp"

class camera {
public:
    camera(const vec3& lookfrom, const vec3& lookat, const vec3& vup, float vfov, float aspect) {
        vec3 u,v,w;

        float theata = vfov * M_PI/180;
        float half_height = tan(theata/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w,u);

        lower_left_corner = vec3(-half_width, -half_height, -1.0f);
        lower_left_corner = origin - half_width * u - half_height * v - w;
        horizontal = 2 * half_width * u;
        vertical = 2 * half_height * v;
    }

    ray get_ray(float u, float v) {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //OFFTRACER_CAMERA_HH
