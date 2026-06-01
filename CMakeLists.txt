cmake_minimum_required(VERSION 3.10)

project(ZedQuad)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_STANDARD 20)

add_library(zedquad STATIC
src/comptime/comptime.cpp
src/comptime/comptime_c.cpp
)

target_include_directories(zedquad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)