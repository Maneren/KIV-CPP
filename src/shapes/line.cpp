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
