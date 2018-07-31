//
// Created by stel on 31/7/2018.
//

#ifndef OFFTRACER_RAY_HPP
#define OFFTRACER_RAY_HPP

#include "vec3.hpp"

class ray {
public:
    ray() {}
    ray(const vec3& a, const vec3& b) : origin(a), direction(b) { }
    vec3 point_at_parameter(float t) const { return origin + t*direction; }

    vec3 origin;
    vec3 direction;
};

#endif //OFFTRACER_RAY_HPP
