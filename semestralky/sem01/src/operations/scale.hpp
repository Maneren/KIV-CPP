#include "../vector.hpp"
#include "operation.hpp"

class Scale : public IOperation
{
public:
  Scale(Point center, float angle) : center(center), magnitude(angle) {}
  Point transform(Point point) override;
  std::string display() override
  {
    return std::format("Scale({}, {})", center, magnitude);
  }
  ~Scale() override = default;

private:
  const Point center;
  const float magnitude;
};
