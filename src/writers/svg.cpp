#include "svg.hpp"

void SVGWriter::write(Scene &scene) {
  auto dimensions = scene.get_dimensions();
  out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
  out << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\""
      << dimensions.x << "\" height=\"" << dimensions.y << "\">\n";

  for (auto &shape : scene.get_shapes()) {
    shape->draw_svg(out);
  }

  out << "</svg>\n";
}
