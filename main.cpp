#include "bvh_node.hh"
#include "camera.hh"
#include "dialectric.hh"
#include "hitable.hh"
#include "hitable_list.hh"
#include "lambertian.hh"
#include "material.hh"
#include "metal.hh"
#include "movine_sphere.hh"
#include "ray.hpp"
#include "sphere.hh"
#include <chrono>
#include <fstream>
#include <iostream>


constexpr const int width = 1200;
constexpr const int height = 800;
const int ns = 10;

vec3 color( const ray &r, hitable *world, int depth ) {

  hit_record rec;
  if ( world->hit( r, 0.001, MAXFLOAT, rec ) ) {
    ray scattered;
    vec3 attenuation;
    if ( depth < 50 &&
         rec.mat_ptr->scatter( r, rec, attenuation, scattered ) ) {
      return attenuation * color( scattered, world, depth + 1 );
    } else {
      return vec3( 0, 0, 0 );
    }
  } else {
    vec3 unit_direction = unit_vector( r.direction );
    float t = 0.5 * ( unit_direction.y() + 1.0 );
    // return vec3(0.1, 0.1, 0.1);
    return ( 1.0 - t ) * vec3( 1.0, 1.0, 1.0 ) + t * vec3( 0.5, 0.7, 1.0 );
  }
}

hitable *random_scene() {
  int n = 500;
  hitable **list = new hitable *[ n + 1 ];
  list[ 0 ] = new sphere( vec3( 0, -1000, 0 ), 1000,
                          new lambartian( vec3( 0.5, 0.5, 0.5 ) ) );
  int i = 1;
  for ( int a = -11; a < 11; a++ ) {
    for ( int b = -11; b < 11; b++ ) {
      float choose_mat = drand48();
      vec3 center( a + 0.9 * drand48(), 0.2, b + 0.9 * drand48() );
      if ( ( center - vec3( 4, 0.2, 0 ) ).length() > 0.9 ) {
        if ( choose_mat < 0.8 ) {    // diffuse
          list[ i++ ] =
              new sphere( center, 0.2,
                          new lambartian( vec3( drand48() * drand48(),
                                                drand48() * drand48(),
                                                drand48() * drand48() ) ) );
        } else if ( choose_mat < 0.95 ) {    // metal
          list[ i++ ] = new sphere(
              center, 0.2,
              new metal( vec3( 0.5 * ( 1 + drand48() ), 0.5 * ( 1 + drand48() ),
                               0.5 * ( 1 + drand48() ) ),
                         0.5 * drand48() ) );
        } else {    // glass
          list[ i++ ] = new sphere( center, 0.2, new dialectric( 1.5 ) );
        }
      }
    }
  }

  list[ i++ ] = new sphere( vec3( 0, 1, 0 ), 1.0, new dialectric( 1.5 ) );
  list[ i++ ] = new sphere( vec3( -4, 1, 0 ), 1.0,
                            new lambartian( vec3( 0.4, 0.2, 0.1 ) ) );
  list[ i++ ] = new sphere( vec3( 4, 1, 0 ), 1.0,
                            new metal( vec3( 0.7, 0.6, 0.5 ), 0.0 ) );

  return new bvh_node( list, i, 0.0f, 1.0f );
}

int main() {

  std::ofstream file( "image.ppm" );
  file << "P3\n" << width << " " << height << "\n255\n";

  float dist_to_focus = 10.0f;
  float aperture = 0.1;

  camera cam( vec3( 13.0f, 2.0f, 3.0f ), vec3( 0.0f, 0.0f, 0.0f ),
              vec3( 0.0f, 1.0f, 0.0f ), 20.0f, float( width ) / float( height ),
              aperture, dist_to_focus, 0.0f, 0.0f );

  auto start_time = std::chrono::high_resolution_clock::now();


  // hitable *list[ 5 ];
  // list[ 0 ] = new sphere( vec3( 0.0f, 0.0f, -1.0f ), 0.5f,
  //                         new lambartian( vec3( 0.1, 0.2, 0.5 ) ) );
  // list[ 1 ] = new sphere( vec3( 0.0f, -100.5f, -1.0f ), 100.0f,
  //                         new lambartian( vec3( 0.8, 0.8, 0.0 ) ) );
  // list[ 2 ] = new sphere( vec3( 1.0f, 0.0f, -1.0f ), 0.5f,
  //                         new metal( vec3( 0.8, 0.6, 0.2 ), 0.0f ) );
  // list[ 3 ] =
  //     new sphere( vec3( -1.0f, 0.0f, -1.0f ), 0.5f, new dialectric( 1.5f ) );
  // list[ 4 ] =
  //     new sphere( vec3( -1.0f, 0.0f, -1.0f ), -0.45f, new dialectric( 1.5f )
  //     );
  //
  hitable *world = random_scene();
  // hitable *world = new hitable_list( list, 5 );

  for ( int j = height - 1; j >= 0; j-- ) {
    for ( int i = 0; i < width; i++ ) {
      vec3 col( 0.0f, 0.0f, 0.0f );

      for ( int s = 0; s < ns; s++ ) {

        float u = float( i + drand48() ) / float( width );
        float v = float( j + drand48() ) / float( height );

        ray r = cam.get_ray( u, v );
        col += color( r, world, 0 );
      }

      col /= float( ns );
      col = vec3( sqrt( col[ 0 ] ), sqrt( col[ 1 ] ), sqrt( col[ 2 ] ) );

      int ir = int( 255.99 * col[ 0 ] );
      int ig = int( 255.99 * col[ 1 ] );
      int ib = int( 255.99 * col[ 2 ] );

      file << ir << " " << ig << " " << ib << "\n";
    }
  }

  auto stop_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> total_time = stop_time - start_time;

  std::cout << "Total rendering time: " << total_time.count() << " s\n";

  file.close();

  return 0;
}
