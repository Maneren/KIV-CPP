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

void Circle::draw_raster(std::vector<std::vector<bool>> &matrix) {
  auto r = radius();
  int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
  do {
    matrix[center.y + y][center.x - x] = true;
    matrix[center.y - x][center.x - y] = true;
    matrix[center.y - y][center.x + x] = true;
    matrix[center.y + x][center.x + y] = true;

    r = err;

    if (r <= y) {
      err += ++y * 2 + 1; /* e_xy+e_y < 0 */
    }

    if (r > x || err > y) {
      err += ++x * 2 + 1; /* e_xy+e_x > 0 or no 2nd y-step */
    }

  } while (x < 0);
}
