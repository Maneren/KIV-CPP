#pragma once
#include "../operations/operation.hpp"
#include <string>

class IShape {
public:
  virtual void transform(IOperation &op) = 0;
  virtual std::string display() = 0;
  virtual ~IShape() = default;
};
