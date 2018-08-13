//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_CAMERA_HH
#define OFFTRACER_CAMERA_HH

#include "vec3.hpp"
#include "ray.hpp"

class camera {
public:
    camera() {
        lower_left_corner = vec3(-2.0f, -1.0f, -1.0f);
        horizontal = vec3(4.0f, 0.0f, 0.0f);
        vertical = vec3(0.0f, 2.0f, 0.0f);
        origin = vec3(0.0f, 0.0f, 0.0f);
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
