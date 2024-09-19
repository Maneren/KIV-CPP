#include "scale.hpp"

Point Scale::transform(Point point) {
  auto x = point.x * angle / 100;
  auto y = point.y * angle / 100;
  return Point(float(x), float(y));
}
