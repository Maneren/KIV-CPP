#include "../vector.hpp"
#include "operation.hpp"
#include <cmath>

class Rotate : public IOperation {
public:
  Rotate(Point center, float angle)
      : center(center), angle(angle * M_PI / 180) {}
  Point transform(Point point) override;
  std::string display() override {
    return std::format("Rotate({}, {})", center, angle);
  }
  ~Rotate() = default;

private:
  const Point center;
  const float angle;
};
