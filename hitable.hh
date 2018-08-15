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

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refreacted) {
    vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if ( discriminant > 0 ) {
        refreacted = ni_over_nt * (uv - n * dt ) - n * sqrt(discriminant);
        return true;
    } else {
        return false;
    }
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1-r0) * pow((1 - cosine), 5);
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
