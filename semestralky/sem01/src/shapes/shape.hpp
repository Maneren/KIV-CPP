#pragma once
#include "../operations/operation.hpp"
#include <iostream>
#include <string>
#include <vector>

class IShape {
public:
  /// Apply the operation to the given shape
  virtual void transform(const IOperation &op) = 0;
  /// Display the shape
  virtual std::string display() const = 0;
  /// Draw the shape in SVG
  virtual void draw_svg(std::ostream &out) const = 0;
  /// Draw the shape in raster
  virtual void draw_raster(std::vector<std::vector<bool>> &matrix) const = 0;
  virtual ~IShape() = default;
};
