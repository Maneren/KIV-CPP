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
