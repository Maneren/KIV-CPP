#include "line.hpp"

void Line::transform(IOperation &op) {
  start = op.transform(start);
  end = op.transform(end);
}
