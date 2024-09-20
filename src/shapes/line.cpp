#include "line.hpp"

void Line::transform(IOperation &op) {
  start = op.transform(start);
  end = op.transform(end);
}

void Line::draw_svg(std::ostream &out) {
  out << "<line x1=\"" << start.x << "\" y1=\"" << start.y << "\" x2=\""
      << end.x << "\" y2=\"" << end.y
      << "\" stroke=\"black\" stroke-width=\"2\"/>\n";
}

void Line::draw_raster(std::vector<std::vector<bool>> &matrix) {
  float x = start.x, y = start.y;

  int dx = std::abs(end.x - start.x), sx = start.x < end.x ? 1 : -1;
  int dy = -std::abs(end.y - start.y), sy = start.y < end.y ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  for (;;) { /* loop */
    matrix[y][x] = true;
    if (x == end.x && y == end.y)
      break;
    e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x += sx;
    } /* e_xy+e_x > 0 */
    if (e2 <= dx) {
      err += dx;
      y += sy;
    } /* e_xy+e_y < 0 */
  }
}
