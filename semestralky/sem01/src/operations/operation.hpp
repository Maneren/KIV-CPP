#pragma once

#include "../vector.hpp"

class IOperation {
public:
  /// Apply the operation to the given point
  virtual Point operator()(const Point point) const = 0;
  /// Display the operation
  virtual std::string display() const = 0;
  virtual ~IOperation() = default;
};
