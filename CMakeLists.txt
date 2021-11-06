cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 14)

project(globalProject)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/libs)
add_subdirectory(graphic_libs/ncurses)
add_subdirectory(graphic_libs/sdl)
add_subdirectory(graphic_libs/sfml)
add_subdirectory(game_libs/snake)
add_subdirectory(core)
