#include "rect.hpp"

void Rect::transform(IOperation &op) {
  start = op.transform(start);
  end = op.transform(end);
}
