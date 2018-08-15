//
// Created by stel on 15/8/2018.
//

#ifndef OFFTRACER_DIALECTRIC_HH
#define OFFTRACER_DIALECTRIC_HH

#include "material.hh"

class dialectric : public material {
public:
    dialectric(float ri) : ref_idx(ri) { }
    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    float ref_idx;
};

bool dialectric::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {

    vec3 outward_normal;
    vec3 reflected = reflect(r_in.direction, rec.normal);
    float ni_over_nt;
    attenuation = vec3(1.0f, 1.0f, 1.0f);
    vec3 refracted;
    float reflect_prob;
    float cosine;

    if ( dot(r_in.direction, rec.normal) > 0 ) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.direction, rec.normal) / r_in.direction.length();
    } else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0f / ref_idx;
        cosine = -dot(r_in.direction, rec.normal) / r_in.direction.length();
    }

    if ( refract(r_in.direction, outward_normal, ni_over_nt, refracted) ) {
        reflect_prob = schlick(cosine, ref_idx);
    } else {
        scattered = ray(rec.p, reflected);
        reflect_prob = 1.0f;
    }

    if ( drand48() < reflect_prob ) {
        scattered = ray(rec.p, reflected);
    } else {
        scattered = ray(rec.p, refracted);
    }

    return true;

}

#endif //OFFTRACER_DIALECTRIC_HH
