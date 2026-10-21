cmake_minimum_required(VERSION 3.16)
project(RayTracer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(raytracer main.cpp)
 target_compile_options(raytracer PRIVATE -Wall -Wextra)