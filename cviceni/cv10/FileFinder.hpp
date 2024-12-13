#include <filesystem>
#include <string>
#include <vector>

std::vector<std::tuple<std::string, size_t>>
FindWithExtension(std::string ext, std::filesystem::path dir);

std::vector<std::filesystem::path> FindInFiles(std::string str,
                                               std::filesystem::path dir);
