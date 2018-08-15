//
// Created by stel on 14/8/2018.
//

#ifndef OFFTRACER_MATERIAL_HH
#define OFFTRACER_MATERIAL_HH

#include "ray.hpp"
#include "hitable.hh"

class material {
public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

#endif //OFFTRACER_MATERIAL_HH
