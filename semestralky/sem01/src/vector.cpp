#include "vector.hpp"
#include <cmath>
#include <format>

std::string Vec2::display() const { return std::format("({}, {})", x, y); }

float Vec2::magnitude() const { return std::sqrt(x * x + y * y); }
