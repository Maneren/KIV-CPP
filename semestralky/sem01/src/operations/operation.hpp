#pragma once
#include "../vector.hpp"

class IOperation {
public:
  /// Apply the operation to the given point
  virtual Point transform(Point point) = 0;
  /// Display the operation
  virtual std::string display() = 0;
  virtual ~IOperation() = default;
};
