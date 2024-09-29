#include "rect.hpp"
#include "line.hpp"

void Rect::transform(IOperation &op) {
  start = op.transform(start);
  end = op.transform(end);

  if (start.x > end.x) {
    std::swap(start.x, end.x);
  }
  if (start.y > end.y) {
    std::swap(start.y, end.y);
  }
}

void Rect::draw_svg(std::ostream &out) {
  out << "<rect x=\"" << start.x << "\" y=\"" << start.y << "\" width=\""
      << end.x - start.x << "\" height=\"" << end.y - start.y
      << "\" fill=\"none\" stroke=\"black\" stroke-width=\"2\"/>\n";
}

void Rect::draw_raster(std::vector<std::vector<bool>> &matrix) {
  Line top({start.x, start.y}, {end.x, start.y});
  top.draw_raster(matrix);
  Line bottom({start.x, end.y}, {end.x, end.y});
  bottom.draw_raster(matrix);
  Line left({start.x, start.y}, {start.x, end.y});
  left.draw_raster(matrix);
  Line right({end.x, start.y}, {end.x, end.y});
  right.draw_raster(matrix);
}
