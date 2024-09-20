#pragma once
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
