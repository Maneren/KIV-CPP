#include "rotate.hpp"
#include <cmath>
#include <math.h>

Point Rotate::transform(Point point) {
  auto x = cos(angle) * (point.x - center.x) -
           sin(angle) * (point.y - center.y) + center.x;
  auto y = sin(angle) * (point.x - center.x) +
           cos(angle) * (point.y - center.y) + center.y;

  return Point(x, y);
}
