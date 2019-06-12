//
// Created by stel on 13/8/2018.
//

#ifndef OFFTRACER_CAMERA_HH
#define OFFTRACER_CAMERA_HH

#include "ray.hpp"
#include "vec3.hpp"

vec3 random_in_unit_disk() {
  vec3 p;
  do {
    p = 2.0f * vec3( drand48(), drand48(), 0.0f ) - vec3( 1.0f, 1.0f, 0.0f );
  } while ( dot( p, p ) >= 1.0f );

  return p;
}

class camera {
public:
  camera( const vec3 &lookfrom, const vec3 &lookat, const vec3 &vup, float vfov,
          float aspect, float aperture, float focus_dist, float t0, float t1 ) {

    time0 = t0;
    time1 = t1;
    lens_radius = aperture / 2;

    // theta in degrees
    float theta = vfov * M_PI / 180;
    origin = lookfrom;
    // half theta
    float half_height = tan( theta / 2 );

    // We consider the aspect ratio here to fix the squashed pixels
    // e.g ( if we have more pixels in x than y, so the image is not perfect
    // square)
    float half_width = aspect * half_height;

    w = unit_vector( lookfrom - lookat );
    u = unit_vector( cross( vup, w ) );
    v = cross( w, u );
    // for example, if fov is 90 deg, and aspect is 2 (600*300), the
    // lower_left_corner would be (-2, -1, -1)
    // lower_left_corner = vec3(-half_width, half_height, -1.0f);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
    // why 2 * half width? so the horizontal axis if
    // in rang from [-2, 2]
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
  }

  ray get_ray( float s, float t ) {
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x()  + v * rd.y();
    // Generate random rays between time0 and time1
    float time = time0 + drand48() * (time0 - time1);
    return ray( origin + offset,
                lower_left_corner + s * horizontal + t * vertical - origin - offset, time );
  }

  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
  vec3 u,v,w;
  float time0, time1;
  float lens_radius;
};

#endif    // OFFTRACER_CAMERA_HH
