#pragma once
#include "../operations/operation.hpp"
#include <iostream>
#include <string>
#include <vector>

class IShape {
public:
  /// Apply the operation to the given shape
  virtual void transform(IOperation &op) = 0;
  /// Display the shape
  virtual std::string display() = 0;
  /// Draw the shape in SVG
  virtual void draw_svg(std::ostream &out) = 0;
  /// Draw the shape in raster
  virtual void draw_raster(std::vector<std::vector<bool>> &matrix) = 0;
  virtual ~IShape() = default;
};
