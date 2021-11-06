cmake_minimum_required(VERSION 3.17)
project(sdl2)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_library(sdl2 SHARED sdl.cpp sdl.h)
set_target_properties(sdl2 PROPERTIES PREFIX "arcade_")
