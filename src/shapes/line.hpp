#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Line : public IShape {
public:
  Line(Point start, Point end) : start(start), end(end) {}
  void transform(IOperation &op) override;
  std::string display() override {
    return std::format("line {} -> {}", start.display(), end.display());
  };
  void draw_svg(std::ostream &out) override;
  void draw_raster(std::vector<std::vector<bool>> &matrix) override;
  ~Line() override = default;

private:
  /// Start point of the line
  Point start;
  /// End point of the line
  Point end;
};
