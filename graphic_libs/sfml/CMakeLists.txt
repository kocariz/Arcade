cmake_minimum_required(VERSION 3.17)
project(sfml)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_library(sfml SHARED sfml.cpp sfml.h)
set_target_properties(sfml PROPERTIES PREFIX "arcade_")
