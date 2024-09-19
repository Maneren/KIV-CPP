#pragma once

#include "../vector.hpp"

class IWriter {
public:
  virtual void write(Scene &scene, Dimensions dims);
  virtual ~IWriter() {}
};
