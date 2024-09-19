#pragma once
#include "defs.hpp"
#include "shapes/shape.hpp"
#include <vector>

class Scene {
public:
  Scene(Dimensions dimensions) : dimensions(dimensions) {}
  ~Scene() {}

private:
  Dimensions dimensions;
  std::vector<IShape> shapes;
};
