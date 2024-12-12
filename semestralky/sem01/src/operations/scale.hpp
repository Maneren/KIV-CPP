#pragma once

#include "../vector.hpp"
#include "operation.hpp"
#include <format>

class Scale final : public IOperation {
public:
  Scale(const Point center, const float angle)
      : center(center), magnitude(angle) {}
  Point operator()(const Point point) const override final;
  std::string display() const override final {
    return std::format("Scale({}, {})", center, magnitude);
  }
  ~Scale() override final = default;

private:
  const Point center;
  const float magnitude;
};
