#pragma once
#include <format>
#include <string>

struct Vec2 {
  Vec2() : x(0), y(0) {}
  Vec2(float x, float y) : x(x), y(y) {}
  float x;
  float y;
  /// Display the vector
  std::string display();

  Vec2 operator+(Vec2 v2);
  Vec2 operator-(Vec2 v2);
  Vec2 operator*(float scalar);

  /// Get the magnitude of the vector
  float magnitude();
};

using Point = Vec2;
using Dimensions = Vec2;

template <> struct std::formatter<Vec2> {
  constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

  auto format(const Vec2 &vec, std::format_context &ctx) const {
    return std::format_to(ctx.out(), "({}, {})", vec.x, vec.y);
  }
};
