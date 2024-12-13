#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <regex>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::tuple<std::string, size_t>>
FindWithExtension(std::string ext, std::filesystem::path dir) {
  return std::filesystem::directory_iterator(dir) |
         std::views::filter([&ext](auto const &entry) {
           return entry.path().extension() == ext;
         }) |
         std::views::transform([](auto const &entry) {
           return std::make_tuple(entry.path().string(), entry.file_size());
         }) |
         std::ranges::to<std::vector>();
}

std::vector<std::filesystem::path> FindInFiles(std::string str,
                                               std::filesystem::path dir) {
  return std::filesystem::directory_iterator(dir) |
         std::views::filter([](auto const &entry) {
           return entry.is_regular_file() && entry.path().extension() == ".txt";
         }) |
         std::views::filter([&, regex = std::regex(str)](auto const &entry) {
           std::stringstream buffer;
           buffer << std::ifstream(entry.path()).rdbuf();
           return std::regex_search(buffer.str(), regex);
         }) |
         std::views::transform(&std::filesystem::directory_entry::path) |
         std::ranges::to<std::vector>();
}
