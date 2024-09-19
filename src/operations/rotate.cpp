#include "rotate.hpp"
#include <cmath>
#include <math.h>

Point Rotate::transform(Point point) {
  auto x = std::lround(cos(angle) * (point.x - center.x) -
                       sin(angle) * (point.y - center.y) + center.x);
  auto y = std::lround(sin(angle) * (point.x - center.x) +
                       cos(angle) * (point.y - center.y) + center.y);

  return Point(float(x), float(y));
}
