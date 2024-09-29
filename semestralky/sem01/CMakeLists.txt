cmake_minimum_required(VERSION 3.30)

project(
  KIV_CPP_Sem01
  VERSION 1.0
  DESCRIPTION "Semester project #1 for KIV/CPP"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(
  drawing
  src/config.cpp
  src/config.hpp
  src/factory.hpp
  src/main.cpp
  src/operations/operation.hpp
  src/operations/rotate.cpp
  src/operations/rotate.hpp
  src/operations/scale.cpp
  src/operations/scale.hpp
  src/operations/translate.cpp
  src/operations/translate.hpp
  src/scene.cpp
  src/scene.hpp
  src/shapes/circle.cpp
  src/shapes/circle.hpp
  src/shapes/line.cpp
  src/shapes/line.hpp
  src/shapes/rect.cpp
  src/shapes/rect.hpp
  src/shapes/shape.hpp
  src/vector.cpp
  src/vector.hpp
  src/writers/pgm.cpp
  src/writers/pgm.hpp
  src/writers/svg.cpp
  src/writers/svg.hpp
  src/writers/writer.hpp)
