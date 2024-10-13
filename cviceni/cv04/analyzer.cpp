#include "analyzer.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <stdexcept>

CAnalyzer::CAnalyzer(std::vector<double> &&numbers) noexcept
    : mNumbers(numbers) {
  // NOTE: v teto metode nic nemente!
}

CAnalyzer CAnalyzer::Create(const std::string &fileName) {
  // NOTE: v teto metode nic nemente!

  std::vector<double> numbers;

  // otevre soubor
  std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

  if (!ifs.is_open()) {
    throw std::invalid_argument{"Nelze otevrit soubor " + fileName};
  }

  // zjisti velikost a pole cisel zvetsi, aby se tam cisla vesla
  ifs.seekg(0, std::ios::end);
  numbers.resize(ifs.tellg() / sizeof(double));
  ifs.seekg(0, std::ios::beg);

  // precte obsah souboru
  ifs.read(reinterpret_cast<char *>(numbers.data()),
           numbers.size() * sizeof(double));

  // overi, ze se precetlo vsechno
  if (ifs.gcount() != numbers.size() * sizeof(double)) {
    throw std::runtime_error{"Nelze precist cisla ze souboru " + fileName};
  }

  return CAnalyzer(std::move(numbers));
}

void CAnalyzer::Cache_Chunk_Averages() {
  /*
   * Implementacni poznamka:
   * pomoci algoritmu, ranges a views se pokuste vypocitat prumery vsech balicku
   * hodnot hodnoty se v souboru nachazeji po 10, tj. pokud je v souboru 50
   * cisel, jde o 5 balicku Vytvorte si atribut v teto tride a predpocitejte do
   * nej prumery z techto balicku cisel (na prikladu vyse tedy vypoctete 5
   * prumeru)
   */

  mChunkAverages = mNumbers |
                   std::views::chunk(CAnalyzer::Measurements_Per_Chunk) |
                   std::views::transform([](const auto &chunk) {
                     return std::accumulate(chunk.begin(), chunk.end(), 0.0) /
                            CAnalyzer::Measurements_Per_Chunk;
                   }) |
                   std::ranges::to<std::vector>();
}

double CAnalyzer::Get_Min_Chunk_Average() const {
  /*
   * Implementacni poznamka:
   * tohle jde udelat na jednu radku, tj.: return ...;
   */

  if (mChunkAverages.empty())
    throw not_cached_yet_exception{};

  return *(std::ranges::min_element(mChunkAverages));
}

double CAnalyzer::Get_Max_Chunk_Average() const {
  /*
   * Implementacni poznamka:
   * tohle jde udelat na jednu radku, tj.: return ...;
   */

  if (mChunkAverages.empty())
    throw not_cached_yet_exception{};

  return *(std::ranges::max_element(mChunkAverages));
}

std::array<double, CAnalyzer::Measurements_Per_Chunk>
CAnalyzer::Get_Piecewise_Averages() {
  /*
   * Implementacni poznamka:
   * pomoci algoritmu, ranges a views se pokuste vypocitat prumery pres sloupce
   * hodnot, tj. jestlize se nachazi v souboru hodnoty po 10 cislech, vypoctete
   * 10 prumeru napr. v prvnim prumeru budou zahrnuty indexy prvku 0, 10, 20,
   * 30, ... ve druhem indexy prvku 1, 11, 21, 31, ...
   */

  auto results = std::ranges::fold_left(
      mNumbers | std::views::chunk(Measurements_Per_Chunk),
      std::array<double, Measurements_Per_Chunk>{0},
      [](auto &&result, const auto &chunk) {
        std::ranges::transform(chunk, result, result.begin(), std::plus<>{});
        return result;
      });

  std::ranges::transform(results, results.begin(),
                         [count = mNumbers.size() / Measurements_Per_Chunk](
                             double sum) { return sum / count; });

  return results;
}
