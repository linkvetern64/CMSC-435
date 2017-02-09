cmake_minimum_required(VERSION 3.6)
project(proj)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RayTracer.cpp RayTracer.h Polygon.cpp Polygon.h Sphere.cpp Sphere.h)
add_executable(proj ${SOURCE_FILES})