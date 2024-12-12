#include "writer.hpp"

class PGMWriter final : public IWriter {
public:
  PGMWriter(std::ostream &out) : IWriter(out) {}
  void write(const Scene &scene) override final;
  ~PGMWriter() override final = default;
};
