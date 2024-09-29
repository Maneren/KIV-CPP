#pragma once
#include "vector.hpp"
#include <filesystem>

class Config {
public:
  Config() = default;
  Config(int argc, char *argv[]);

  std::filesystem::path get_input_file() const { return input_file; }
  std::filesystem::path get_output_file() const { return output_file; }
  Dimensions get_dimensions() const { return dimensions; }

private:
  std::filesystem::path input_file;
  std::filesystem::path output_file;
  Dimensions dimensions;

  void validateArguments(int argc, char *argv[]);
  void parseDimensions(const std::string &dims);
};