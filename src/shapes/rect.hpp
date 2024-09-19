#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Rect : public IShape {
public:
  Rect(Point start, Dimensions dimensions) : start(start) {
    end.x = start.x + dimensions.x;
    end.y = start.y + dimensions.y;
  }
  void transform(IOperation &op) override;
  std::string display() override {
    return std::format("Rect({}, {})", start, end);
  };

private:
  /// Top-left point of the rect
  Point start;
  /// Bottom-right point of the rect
  Point end;
};
