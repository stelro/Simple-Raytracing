cmake_minimum_required(VERSION 3.9)
project(offtracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(offtracer vec3.hpp main.cpp ray.hpp hitable.hh sphere.hh hitable_list.hh camera.hh material.hh lambertian.hh metal.hh)