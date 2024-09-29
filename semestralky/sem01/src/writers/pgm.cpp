#include "pgm.hpp"
#include <vector>

void PGMWriter::write(Scene &scene) {
  auto dimensions = scene.get_dimensions();
  out << "P2\n";
  out << dimensions.x << " " << dimensions.y << "\n";
  out << "255\n";

  auto matrix = std::vector<std::vector<bool>>(
      dimensions.y, std::vector<bool>(dimensions.x, false));

  for (auto &shape : scene.get_shapes()) {
    shape->draw_raster(matrix);
  }

  for (auto row : matrix) {
    for (auto pixel : row) {
      out << (pixel ? "0 " : "255 ");
    }
    out << "\n";
  }

  out.flush();
}
