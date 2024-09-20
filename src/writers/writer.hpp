#pragma once
#include "../scene.hpp"
#include <iostream>

class IWriter {
public:
  IWriter(std::ostream &out) : out(out) {}
  virtual void write(Scene &scene) = 0;
  virtual ~IWriter() = default;

protected:
  std::ostream &out;
};
