#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Circle : public IShape {
public:
  Circle(Point center, float radius)
      : center(center), radiusPoint({center.x, center.y + radius}) {
    if (radius < 0) {
      throw std::invalid_argument("Circle radius cannot be negative");
    }
  };
  void transform(const IOperation &op) override;
  std::string display() const override {
    return std::format("circle {}, {}", center.display(), radius());
  };
  void draw_svg(std::ostream &out) const override;
  void draw_raster(std::vector<std::vector<bool>> &matrix) const override;
  float radius() const { return (radiusPoint - center).magnitude(); }
  ~Circle() override = default;

private:
  /// The center of the circle
  Point center;
  /// A point in the circle, the defines the radius
  Point radiusPoint;
};
