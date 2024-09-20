#pragma once
#include "../vector.hpp"
#include "shape.hpp"
#include <format>

class Line : public IShape {
public:
  Line(Point start, Point end) : start(start), end(end) {}
  void transform(IOperation &op) override;
  std::string display() override {
    return std::format("Line({} -> {})", start.display(), end.display());
  };
  ~Line() = default;

private:
  /// Start point of the line
  Point start;
  /// End point of the line
  Point end;
};
