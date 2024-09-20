#include "rect.hpp"

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
