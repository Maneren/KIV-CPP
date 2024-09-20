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
  auto x = static_cast<int>(start.x);
  auto y = static_cast<int>(start.y);

  auto end_x = static_cast<int>(end.x);
  auto end_y = static_cast<int>(end.y);

  int delta_x = std::abs(end_x - x);
  int step_x = start.x < end.x ? 1 : -1;

  int delta_y = -std::abs(end_y - y);
  int step_y = start.y < end.y ? 1 : -1;

  int error = delta_x + delta_y;
  int error_xy;

  while (true) {
    // Ensure the coordinates are within the bounds of the matrix
    if (x >= 0 && x < matrix[0].size() && y >= 0 && y < matrix.size()) {
      matrix[y][x] = true;
    }

    if (x == end_x && y == end_y) {
      break;
    }

    error_xy = 2 * error;

    if (error_xy >= delta_y) {
      error += delta_y;
      x += step_x;
    }

    if (error_xy <= delta_x) {
      error += delta_x;
      y += step_y;
    }
  }
}
