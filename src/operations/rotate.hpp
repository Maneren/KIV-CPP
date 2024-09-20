#include "../vector.hpp"
#include "operation.hpp"

class Rotate : public IOperation {
public:
  Rotate(Point center, float angle) : center(center), angle(angle) {}
  Point transform(Point point) override;
  std::string display() override {
    return std::format("Rotate({}, {})", center, angle);
  }
  ~Rotate() = default;

private:
  const Point center;
  const float angle;
};
