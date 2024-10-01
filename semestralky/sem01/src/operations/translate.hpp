#pragma once

#include "../vector.hpp"
#include "operation.hpp"
#include <format>

class Translate : public IOperation {
public:
  Translate(const Vec2 delta) : delta(delta) {}
  Point operator()(const Point point) const override;
  std::string display() const override {
    return std::format("Translate({})", delta);
  }
  ~Translate() override = default;

private:
  const Vec2 delta;
};
