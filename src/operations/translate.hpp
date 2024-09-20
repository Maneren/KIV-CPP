#include "../vector.hpp"
#include "operation.hpp"

class Translate : public IOperation
{
public:
  explicit Translate(Vec2 delta) : delta(delta) {}
  Point transform(Point point) override;
  std::string display() override { return std::format("Translate({})", delta); }
  ~Translate() override = default;

private:
  const Vec2 delta;
};
