//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_SPHERE_HH
#define OFFTRACER_SPHERE_HH

#include "hitable.hh"

class material;

class sphere : public hitable {
public:
  sphere() {}
  sphere( const vec3 &cen, float r, material *mat )
      : center( cen )
      , radius( r )
      , mat_ptr( mat ) {}
  virtual bool hit( const ray &r, float t_min, float t_max,
                    hit_record &rec ) const override;
  virtual bool bounding_box( float t0, float t1, aabb &box ) const override;
  vec3 center;
  float radius;
  material *mat_ptr;
};

bool sphere::hit( const ray &r, float t_min, float t_max,
                  hit_record &rec ) const {

  vec3 oc = r.origin - center;
  float a = dot( r.direction, r.direction );
  float b = dot( oc, r.direction );
  float c = dot( oc, oc ) - radius * radius;

  float discriminant = b * b - a * c;

  if ( discriminant > 0 ) {
    float temp = ( -b - sqrt( b * b - a * c ) ) / a;
    if ( temp < t_max && temp > t_min ) {
      rec.t = temp;
      rec.mat_ptr = mat_ptr;
      rec.p = r.point_at_parameter( rec.t );
      rec.normal = ( rec.p - center ) / radius;
      return true;
    }

    temp = ( -b + sqrt( b * b - a * c ) ) / a;
    if ( temp < t_max && temp > t_min ) {
      rec.t = temp;
      rec.mat_ptr = mat_ptr;
      rec.p = r.point_at_parameter( rec.t );
      rec.normal = ( rec.p - center ) / radius;
      return true;
    }
  }

  return false;
}

bool sphere::bounding_box( [[maybe_unused]]float t0, [[maybe_unused]]float t1, aabb &box ) const {
  box = aabb( center - vec3( radius, radius, radius ),
              center + vec3( radius, radius, radius ) );
  return true;
}


#endif    // OFFTRACER_SPHERE_HH
