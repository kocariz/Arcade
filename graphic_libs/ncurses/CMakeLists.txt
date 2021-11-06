cmake_minimum_required(VERSION 3.17)
project(ncurses)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_library(ncurses SHARED libncurses.cpp libncurses.h)
set_target_properties(ncurses PROPERTIES PREFIX "arcade_")
