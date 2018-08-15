//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_CAMERA_HH
#define OFFTRACER_CAMERA_HH

#include "vec3.hpp"
#include "ray.hpp"

vec3 random_in_unit_disk() {
    vec3 p;
    do {
        p = 2.0f * vec3(drand48(), drand48(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
    }while (dot(p,p) >= 1.0f);

    return p;
}

class camera {
public:
    camera(const vec3& lookfrom, const vec3& lookat, const vec3& vup, float vfov, float aspect, float aperture, float focus_dist) {
        lens_radius = aperture / 2;
        float theata = vfov * M_PI/180;
        float half_height = tan(theata/2);
        float half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w,u);

        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    ray get_ray(float s, float t) {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

    float lens_radius;
    vec3 u,v,w;
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif //OFFTRACER_CAMERA_HH
