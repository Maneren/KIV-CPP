#include "circle.hpp"

void Circle::transform(IOperation &op) {
  center = op.transform(center);
  radiusPoint = op.transform(radiusPoint);
}

void Circle::draw_svg(std::ostream &out) {
  out << "<circle cx=\"" << center.x << "\" cy=\"" << center.y << "\" r=\""
      << (radiusPoint - center).magnitude()
      << "\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n";
}

bool isWithinBounds(const std::vector<std::vector<bool>> &matrix, int x,
                    int y) {
  return x >= 0 && x < matrix[0].size() && y >= 0 && y < matrix.size();
}

void Circle::draw_raster(std::vector<std::vector<bool>> &matrix) {
  auto radiusInt = static_cast<int>(radius());
  int x = -radiusInt;
  int y = 0;
  int error = 2 - 2 * radiusInt;

  auto centerX = static_cast<int>(center.x);
  auto centerY = static_cast<int>(center.y);

  do {
    int x1 = centerX - x;
    int y1 = centerY + y;
    if (isWithinBounds(matrix, x1, y1)) {
      matrix[y1][x1] = true;
    }

    int x2 = centerX - y;
    int y2 = centerY - x;
    if (isWithinBounds(matrix, x2, y2)) {
      matrix[y2][x2] = true;
    }

    int x3 = centerX + x;
    int y3 = centerY - y;
    if (isWithinBounds(matrix, x3, y3)) {
      matrix[y3][x3] = true;
    }

    int x4 = centerX + y;
    int y4 = centerY + x;
    if (isWithinBounds(matrix, x4, y4)) {
      matrix[y4][x4] = true;
    }

    int errorY = error;

    if (errorY <= y) {
      error += ++y * 2 + 1;
    }

    if (errorY > x || error > y) {
      error += ++x * 2 + 1;
    }
  } while (x < 0);
}
