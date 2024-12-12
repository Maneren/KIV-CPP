#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Rect final : public IShape {
public:
  Rect(Point start, Dimensions dimensions)
      : start(start), end(start + dimensions) {};
  void transform(const IOperation &op) override final;
  std::string display() const override final {
    return std::format("rect {}, {}", start, end - start);
  };
  void draw_svg(std::ostream &out) const override final;
  void draw_raster(std::vector<std::vector<bool>> &matrix) const override final;
  ~Rect() override final = default;

private:
  /// Top-left point of the rect
  Point start;
  /// Bottom-right point of the rect
  Point end;
};
