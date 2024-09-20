[private]
default:
    @just --list

configure:
  cmake -S . -B build

build:
  cmake --build build

sample: build
  ./build/drawing inputs/sample.in inputs/sample.svg 60x60
  ./build/drawing inputs/sample.in inputs/sample.pgm 60x60

complex: build
  ./build/drawing inputs/complex.in inputs/complex.svg 160x160
  ./build/drawing inputs/complex.in inputs/complex.pgm 160x160

clean:
  rm -rf build
