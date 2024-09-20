#include "../vector.hpp"
#include "operation.hpp"

class Translate : public IOperation {
public:
  Translate(Vec2 delta) : delta(delta) {}
  Point transform(Point point) override;
  std::string display() override { return std::format("Translate({})", delta); }
  ~Translate() = default;

private:
  Vec2 delta;
};
