#include "writer.hpp"

class SVGWriter : public IWriter {
public:
  SVGWriter(std::ostream &out) : IWriter(out) {}
  void write(Scene &scene) override;
  void draw_shape(IShape &shape);
  ~SVGWriter() = default;
};
