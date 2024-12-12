#include "writer.hpp"

class SVGWriter final : public IWriter {
public:
  SVGWriter(std::ostream &out) : IWriter(out) {}
  void write(const Scene &scene) override final;
  ~SVGWriter() override final = default;
};
