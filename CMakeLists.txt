cmake_minimum_required (VERSION 3.8)

project (map_homeworks_02_03)
set (CMAKE_CXX_STANDARD 17)

add_executable (map_homeworks_02_03 map_homeworks_02_03.cpp)

target_compile_features(map_homeworks_02_03 PRIVATE cxx_std_17)
