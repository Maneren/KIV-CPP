cmake_minimum_required(VERSION 3.30)

project(
  KIV_CPP_Sem01
  VERSION 1.0
  DESCRIPTION "Semestral exercise #1 for KIV/CPP"
  LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(drawing src/config.cpp src/config.hpp src/defs.hpp src/main.cpp)
