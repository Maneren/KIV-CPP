#include "scale.hpp"

Point Scale::operator()(const Point point) const {
  return (point - center) * magnitude + center;
}
