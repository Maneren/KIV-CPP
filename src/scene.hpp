#pragma once
#include "shapes/shape.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  Scene(Dimensions dimensions) : dimensions(dimensions) {}
  void add_shape(std::unique_ptr<IShape> shape);
  void apply(IOperation &op);
  std::string display();
  ~Scene() {}

private:
  Dimensions dimensions;
  std::vector<std::unique_ptr<IShape>> shapes;
};
