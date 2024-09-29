#include "../vector.hpp"
#include "operation.hpp"
#include <cmath>
#include <numbers>

class Rotate : public IOperation {
public:
  Rotate(Point center, float angle)
      : center(center), angle(angle * std::numbers::pi_v<float> / 180) {}
  Point transform(Point point) override;
  std::string display() override {
    return std::format("Rotate({}, {})", center, angle);
  }
  ~Rotate() override = default;

private:
  const Point center;
  const float angle;
};
