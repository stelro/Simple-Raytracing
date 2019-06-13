//
// Created by stel on 14/8/2018.
//

#ifndef OFFTRACER_LAMBERTIAN_HH
#define OFFTRACER_LAMBERTIAN_HH

#include "material.hh"
#include "texture.hh"

class lambartian : public material {
public:
  lambartian( texture* a)
      : albedo( a ) {}
  bool scatter( const ray &r_in, const hit_record &rec, vec3 &attenuation,
                ray &scattered ) const override;
  texture* albedo;
};

bool lambartian::scatter( const ray &r_in, const hit_record &rec,
                          vec3 &attenuation, ray &scattered ) const {
  vec3 target = rec.p + rec.normal + random_in_unit_sphere();
  scattered = ray( rec.p, target - rec.p, r_in.time );
  attenuation = albedo->value(0, 0, rec.p);
  return true;
}

#endif    // OFFTRACER_LAMBERTIAN_HH
