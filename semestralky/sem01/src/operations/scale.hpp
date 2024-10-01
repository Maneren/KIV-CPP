#pragma once

#include "../vector.hpp"
#include "operation.hpp"
#include <format>

class Scale : public IOperation {
public:
  Scale(const Point center, const float angle)
      : center(center), magnitude(angle) {}
  Point transform(const Point point) const override;
  std::string display() const override {
    return std::format("Scale({}, {})", center, magnitude);
  }
  ~Scale() override = default;

private:
  const Point center;
  const float magnitude;
};
