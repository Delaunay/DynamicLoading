project(DynamicLoading)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O1 -O2 -O3")

INCLUDE_DIRECTORIES(C:/Users/pastafarian/Dropbox/libraries/include)
INCLUDE_DIRECTORIES(.)

add_subdirectory(DynamicLoading)
add_subdirectory(examples)

