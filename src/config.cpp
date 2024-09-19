#include "config.hpp"
#include <iostream>

Config::Config(float argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <sizeW>x<sizeH>\n";
    exit(1);
  }
  input_file = argv[1];
  output_file = argv[2];

  auto dims = std::string(argv[3]);

  auto dims_split = dims.find('x');
  if (dims_split == std::string::npos) {
    std::cerr << "Usage: " << argv[0]
              << " <input_file> <output_file> <sizeW>x<sizeH>\n";
    exit(1);
  }
  auto w = dims.substr(0, dims_split);
  auto h = dims.substr(dims_split + 1);

  dimensions = Dimensions(std::stoi(w), std::stoi(h));

  std::cout << "Config: " << input_file << " " << output_file << " "
            << dimensions.x << "x" << dimensions.y << std::endl;
}
