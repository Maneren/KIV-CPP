#pragma once
#include "shapes/shape.hpp"
#include <memory>
#include <vector>

class Scene {
public:
  /// Create a new scene with the given dimensions
  Scene(Dimensions dimensions) : dimensions(dimensions) {}
  /// Add a shape to the scene
  void add_shape(std::unique_ptr<IShape> shape);
  /// Apply the operation to all shapes in the scene
  void apply(IOperation &op);
  /// Display all shapes in the scene
  std::string display();
  ~Scene() {}

private:
  Dimensions dimensions;
  std::vector<std::unique_ptr<IShape>> shapes;
};
