#pragma once

#include "../vector.hpp"
#include "operation.hpp"
#include <format>
#include <numbers>

class Rotate : public IOperation {
public:
  Rotate(const Point center, const float angle)
      : center(center), angle(angle * std::numbers::pi_v<float> / 180) {}

  Point operator()(const Point point) const override;

  std::string display() const override {
    return std::format("Rotate({}, {})", center, angle);
  }

  ~Rotate() override = default;

private:
  const Point center;
  const float angle;
};
