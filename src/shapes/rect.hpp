#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Rect : public IShape {
public:
  Rect(Point start, Dimensions dimensions)
      : start(start), end(start + dimensions){};
  void transform(IOperation &op) override;
  std::string display() override {
    return std::format("rect {}, {}", start, end - start);
  };
  void draw_svg(std::ostream &out) override;
  void draw_raster(std::vector<std::vector<bool>> &matrix) override;
  ~Rect() = default;

private:
  /// Top-left point of the rect
  Point start;
  /// Bottom-right point of the rect
  Point end;
};
