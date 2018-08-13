//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_HITABLE_HH
#define OFFTRACER_HITABLE_HH

#include "vec3.hpp"
#include "ray.hpp"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
public:
    virtual bool hit(const ray&r , float t_min, float t_max, hit_record& rec) const = 0;
};

#endif //OFFTRACER_HITABLE_HH
