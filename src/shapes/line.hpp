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

private:
  /// Start point of the line
  Point start;
  /// End point of the line
  Point end;
};

// template <> struct std::formatter<Line> {
//   constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin();
//   }
//
//   auto format(const Index &id, std::format_context &ctx) const {
//     return std::format_to(ctx.out(), "Line({})", id.id_);
//   }
// };
