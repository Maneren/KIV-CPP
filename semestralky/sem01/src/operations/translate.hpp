#pragma once

#include "../vector.hpp"
#include "operation.hpp"
#include <format>

class Translate final : public IOperation {
public:
  Translate(const Vec2 delta) : delta(delta) {}
  Point operator()(const Point point) const override final;
  std::string display() const override final {
    return std::format("Translate({})", delta);
  }
  ~Translate() override final = default;

private:
  const Vec2 delta;
};
