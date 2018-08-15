//
// Created by stel on 15/8/2018.
//

#ifndef OFFTRACER_METAL_HH
#define OFFTRACER_METAL_HH

#include "vec3.hpp"
#include "material.hh"

class metal : public material {
public:
    metal(const vec3& a, float f) : albedo(a) {
        if (f < 1) fuzz  = f;
        else fuzz = 1;
    }
    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override {
        vec3 reflected = reflect(unit_vector(r_in.direction), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0);
    }

    vec3 albedo;
    float fuzz;
};

#endif //OFFTRACER_METAL_HH
