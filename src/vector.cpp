#include "vector.hpp"
#include <cmath>
#include <format>

std::string Vec2::display() { return std::format("({}, {})", x, y); }

Vec2 Vec2::operator+(Vec2 v2) { return Vec2(x + v2.x, y + v2.y); }

Vec2 Vec2::operator-(Vec2 v2) { return Vec2(x - v2.x, y - v2.y); }

Vec2 Vec2::operator*(float scalar) { return Vec2(x * scalar, y * scalar); }

float Vec2::magnitude() { return std::sqrt(x * x + y * y); }
