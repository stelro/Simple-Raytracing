//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_HITABLE_HH
#define OFFTRACER_HITABLE_HH

#include "vec3.hpp"
#include "ray.hpp"

class material;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    material *mat_ptr;
};

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v,n) * n;
}

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        /// room for more optimazaitons here
        p = 2.0f * vec3(drand48(), drand48(), drand48()) - vec3(1.0f,1.0f, 1.0f);
    } while ( p.squared_length() >= 1.0f );

    return p;
}

class hitable {
public:
    virtual bool hit(const ray&r , float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //OFFTRACER_HITABLE_HH
