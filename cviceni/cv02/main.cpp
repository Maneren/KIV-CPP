#include <array>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 1) implementujte RAII obal nad souborem ze standardni knihovny C
class RAII_File {
public:
  RAII_File(const std::string &filename, const std::string &mode) {
    file = fopen(filename.c_str(), mode.c_str());

    if (!file) {
      throw std::runtime_error("Cannot open file: " + filename);
    }
  }
  ~RAII_File() { fclose(file); }

  // 2) doplnte metodu Read_Line
  std::string Read_Line() {
    char *line = nullptr;
    size_t len = 0;
    ssize_t read = getline(&line, &len, file);

    if (read != -1) {
      std::string result(line);
      free(line);
      return result;
    }

    free(line);
    return "";
  }

  // 3) doplnte metodu Write_Line
  void Write_Line(const std::string &line) {
    fprintf(file, "%s", line.c_str());
  }

protected:
  FILE *file;
};

constexpr size_t file_count = 3;

// 4) implementujte metodu, ktera vygeneruje obsah do nekolika souboru
void Generate_Files() {
  // a) vytvorte vektor souboru
  // b) vlozte do nej nekolik instanci RAII_File souboru, do kterych budeme
  // zapisovat c) vygenerujte nejaky obsah, ktery do souboru budete vkladat;
  //    - kazdy soubor by mel mit ruzny obsah
  //    - pristupujte ke vsem souborum v cyklu nad vektorem
  std::vector<std::unique_ptr<RAII_File>> files = {};

  for (size_t i = 0; i < file_count; i++) {
    files.push_back(
        std::make_unique<RAII_File>("file" + std::to_string(i) + ".txt", "w"));
  }

  for (size_t i = 0; i < files.size(); i++) {
    // Content # - 0, 1, 2
    files[i]->Write_Line("Content " + std::to_string(i));
  }
}

// 5) implementujte metodu, ktera overi, ze v souborech je skutecne ten obsah,
// ktery tam ma byt
bool Verify_Files() {
  // a) vytvorte vektor souboru
  // b) vlozte do nej nekolik instanci RAII_File souboru, ze kterych budeme cist
  // c) overte, ze v souborech je to, co jste do nich v Generate_Files zapsali
  //    - vrate true, pokud ano, jinak vratte false
  std::vector<std::unique_ptr<RAII_File>> files = {};

  for (size_t i = 0; i < file_count; i++) {
    files.push_back(
        std::make_unique<RAII_File>("file" + std::to_string(i) + ".txt", "r"));
  }

  for (size_t i = 0; i < files.size(); i++)
    if (files[i]->Read_Line() != "Content " + std::to_string(i))
      return false;

  return true;
}

int main() {
  Generate_Files();

  const bool outcome = Verify_Files();

  if (outcome)
    std::cout << "Vse probehlo v poradku" << std::endl;
  else
    std::cerr << "Vyskytla se chyba!" << std::endl;

  return 0;
}
