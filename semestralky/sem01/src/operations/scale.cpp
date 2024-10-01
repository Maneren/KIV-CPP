#include "scale.hpp"

Point Scale::transform(const Point point) const {
  return (point - center) * magnitude + center;
}
