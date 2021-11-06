cmake_minimum_required(VERSION 3.17)
project(nibbler)

set(CMAKE_CXX_STANDARD 14)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
add_library(nibbler SHARED src/snakeGame.cpp include/snakeGame.hpp src/player.cpp include/player.hpp)
set_target_properties(nibbler PROPERTIES PREFIX "arcade_")