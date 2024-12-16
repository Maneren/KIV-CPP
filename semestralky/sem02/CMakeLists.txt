cmake_minimum_required(VERSION 3.30)

project(
  KIV_CPP_Sem02
  VERSION 1.0
  DESCRIPTION "Semester project #2 for KIV/CPP"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(mpcalc src/main.cpp)
