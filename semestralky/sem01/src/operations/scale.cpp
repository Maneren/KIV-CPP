#include "scale.hpp"

Point Scale::transform(Point point) {
  return (point - center) * magnitude + center;
}
