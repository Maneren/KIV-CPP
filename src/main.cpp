#include "config.hpp"
#include "factory.hpp"
#include "operations/operation.hpp"
#include "operations/rotate.hpp"
#include "operations/scale.hpp"
#include "operations/translate.hpp"
#include "scene.hpp"
#include "shapes/circle.hpp"
#include "shapes/line.hpp"
#include "shapes/rect.hpp"
#include "shapes/shape.hpp"
#include "vector.hpp"
#include "writers/pgm.hpp"
#include "writers/svg.hpp"
#include "writers/writer.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  Config config;
  try {
    config = Config(argc, argv);
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  // Read input file
  std::ifstream input_file(config.get_input_file());
  if (!input_file) {
    std::cerr << "Could not open input file: " << config.get_input_file()
              << std::endl;
    return 1;
  }

  Factory<IShape, std::vector<float>> shapeFactory;

  shapeFactory.register_type("line", [](auto args) {
    return args.size() != 4
               ? std::nullopt
               : std::optional{std::make_unique<Line>(Point(args[0], args[1]),
                                                      Point(args[2], args[3]))};
  });

  shapeFactory.register_type("rect", [](auto args) {
    return args.size() != 4
               ? std::nullopt
               : std::optional{std::make_unique<Rect>(
                     Point(args[0], args[1]), Dimensions(args[2], args[3]))};
  });

  shapeFactory.register_type("circle", [](auto args) {
    return args.size() != 3 ? std::nullopt
                            : std::optional{std::make_unique<Circle>(
                                  Point(args[0], args[1]), args[2])};
  });

  Factory<IOperation, std::vector<float>> operationFactory;

  operationFactory.register_type("translate", [](auto args) {
    return args.size() != 2 ? std::nullopt
                            : std::optional{std::make_unique<Translate>(
                                  Vec2(args[0], args[1]))};
  });

  operationFactory.register_type("rotate", [](auto args) {
    return args.size() != 3 ? std::nullopt
                            : std::optional{std::make_unique<Rotate>(
                                  Point(args[0], args[1]), args[2])};
  });

  operationFactory.register_type("scale", [](auto args) {
    return args.size() != 3 ? std::nullopt
                            : std::optional{std::make_unique<Scale>(
                                  Point(args[0], args[1]), args[2])};
  });

  Scene scene{config.get_dimensions()};

  std::string line;
  while (std::getline(input_file, line)) {
    auto type = line.substr(0, line.find(' '));
    auto args_str = line.substr(line.find(' ') + 1);

    std::vector<float> arg_vector;
    std::stringstream ss(args_str);
    float arg;
    while (ss >> arg) {
      arg_vector.push_back(arg);
    }

    if (auto shape = shapeFactory.create(type, arg_vector); shape) {
      scene.add_shape(std::move(*shape));
      continue;
    }

    if (auto transform = operationFactory.create(type, arg_vector); transform) {
      scene.apply_transform(**transform);
      continue;
    }

    std::cerr << "Unknown instruction: '" << type << "'" << std::endl;
    return 1;
  }

  std::ofstream output_file(config.get_output_file());
  if (!output_file) {
    std::cerr << "Could not open output file: " << config.get_output_file()
              << std::endl;
    return 1;
  }

  Factory<IWriter, std::ostream &> writerFactory;

  writerFactory.register_type(
      ".svg", [](auto &output) { return std::make_unique<SVGWriter>(output); });

  writerFactory.register_type(
      ".pgm", [](auto &output) { return std::make_unique<PGMWriter>(output); });

  auto extension = config.get_output_file().extension();

  auto writer = writerFactory.create(extension.string(), output_file);
  if (!writer) {
    std::cerr << "Unknown output file extension: " << extension.string()
              << std::endl;
    return 1;
  }

  writer->get()->write(scene);

  return 0;
}
