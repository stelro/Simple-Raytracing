//
// Created by stel on 31/7/2018.
//

#ifndef OFFTRACER_RAY_HPP
#define OFFTRACER_RAY_HPP

#include "vec3.hpp"

class ray {
public:
  ray() {}
  ray( const vec3 &a, const vec3 &b, float _time = 0.0f )
      : origin( a )
      , direction( b )
      , time( _time ) {}
  vec3 point_at_parameter( float t ) const {
    return origin + t * direction;
  }

  vec3 origin;
  vec3 direction;

  float time;
};

#endif    // OFFTRACER_RAY_HPP
