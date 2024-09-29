#include <iostream>
#include <ostream>
#include <vector>
constexpr int RECORD_COUNT = 100;
constexpr int RECORD_COUNT_NEW = 1000;

struct TRecord {
  int index;
  double value;
};

/*
 * Vyplni zaznamy v poli magickymi hodnotami
 *
 * recs - reference na vector, ktery ma byt vyplnen
 * count - pocet zaznamu, ktere maji byt pridany
 */
void add_records(std::vector<TRecord> &recs, int count) {
  for (int i = 0; i < count; i++) {
    double value =
        static_cast<double>((i * 19) % 29) * 0.1854; // nejaka magie, to je fuk
    recs.push_back({i, value});
  }
}

/*
 * Vypocte prumer ze zadaneho poctu prvku v poli
 *
 * recs - ukazatel na pole se zaznamy
 * start - index prvniho prvku, od ktereho ma byt pocitan prumer
 * count - pocet zaznamu, ze kterych ma byt udelany prumer
 */
double calculate_average(std::vector<TRecord> &recs, int start,
                         int count = -1) {
  double accumulator = 0;

  if (count == -1 || count > recs.size() - start)
    count = recs.size() - start;

  for (int i = 0; i < count; i++)
    accumulator += recs[start + i].value;

  accumulator /= static_cast<double>(count);

  return accumulator;
}

int main(int argc, char **argv) {
  double avg;

  std::vector<TRecord> recs;

  add_records(recs, RECORD_COUNT);

  avg = calculate_average(recs, 0);

  std::cout << "Prumer celeho pole je: " << avg << std::endl;

  avg = calculate_average(recs, 0, RECORD_COUNT / 2);
  std::cout << "Prumer prvni pulky pole je: " << avg << std::endl;
  avg = calculate_average(recs, RECORD_COUNT / 2);
  std::cout << "Prumer druhe pulky pole je: " << avg << std::endl;

  add_records(recs, RECORD_COUNT_NEW - RECORD_COUNT);

  avg = calculate_average(recs, 0);
  std::cout << "Prumer celeho pole je: " << avg << std::endl;

  avg = calculate_average(recs, 0, RECORD_COUNT_NEW / 2);
  std::cout << "Prumer prvni pulky pole je: " << avg << std::endl;
  avg = calculate_average(recs, RECORD_COUNT_NEW / 2);
  std::cout << "Prumer druhe pulky pole je: " << avg << std::endl;

  return 0;
}
