#include "writer.hpp"

class PGMWriter : public IWriter {
public:
  PGMWriter(std::ostream &out) : IWriter(out) {}
  void write(const Scene &scene) override;
  ~PGMWriter() override = default;
};
