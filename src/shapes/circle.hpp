#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Circle : public IShape {
public:
  Circle(Point center, float radius)
      : center(center), radiusPoint({center.x, center.y + radius}){};
  void transform(IOperation &op) override;
  std::string display() override {
    return std::format("Circle({}, {})", center.display(),
                       center.y - radiusPoint.y);
  };
  ~Circle() = default;

private:
  /// The center of the circle
  Point center;
  /// A point in the circle, the defines the radius
  Point radiusPoint;
};
