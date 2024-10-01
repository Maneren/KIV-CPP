#pragma once
#include "vector.hpp"
#include <filesystem>

class Config {
public:
  Config() = default;
  Config(const int argc, const char *const argv[]);

  const std::filesystem::path &get_input_file() const { return input_file; }
  const std::filesystem::path &get_output_file() const { return output_file; }
  Dimensions get_dimensions() const { return dimensions; }

private:
  std::filesystem::path input_file;
  std::filesystem::path output_file;
  Dimensions dimensions;
};
