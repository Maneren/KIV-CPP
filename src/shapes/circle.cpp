#include "circle.hpp"

void Circle::transform(IOperation &op) {
  center = op.transform(center);
  radiusPoint = op.transform(radiusPoint);
}
