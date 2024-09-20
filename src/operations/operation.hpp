#pragma once
#include "../vector.hpp"

class IOperation {
public:
  virtual Point transform(Point point) = 0;
  virtual std::string display() = 0;
  virtual ~IOperation() = default;
};
