#include "config.hpp"

Config::Config(const int argc, const char *const argv[]) {
  if (argc != 4) {
    throw std::invalid_argument(
        std::format("Usage: {} <input_file> <output_file> <sizeW>x<sizeH>",
                    std::string(argv[0])));
  }

  input_file = argv[1];
  output_file = argv[2];

  const std::string dims = argv[3];

  auto dims_split = dims.find('x');
  if (dims_split == std::string::npos) {
    throw std::invalid_argument(
        "Invalid dimensions format. Expected <sizeW>x<sizeH>");
  }

  try {
    auto width = std::stof(dims.substr(0, dims_split));
    auto height = std::stof(dims.substr(dims_split + 1));
    dimensions = Dimensions(width, height);
  } catch (const std::invalid_argument &e) {
    throw std::invalid_argument(
        "Invalid dimensions values. Expected <sizeW>x<sizeH>");
  }
}
