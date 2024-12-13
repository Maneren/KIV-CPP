#include "FileFinder.hpp"
#include <print>

int main() {
  auto files = FindWithExtension(".cpp", "cv10");

  for (auto const &file : files) {
    std::println("{}: {}", std::get<0>(file), std::get<1>(file));
  }

  auto files2 = FindInFiles("Content", std::filesystem::current_path());
  for (auto const &file : files2) {
    std::println("{}", file.filename().string());
  }

  return 0;
}
