#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <random>
#include <ranges>
#include <thread>
#include <vector>

/*
 * Priklad k optimalizaci
 * ======================
 * Tento program UMYSLNE obsahuje neefektivni konstrukce, pouziti nevhodnych
 * datovych struktur, kombinace ridicich struktur, ktere nedavaji uplne smysl,
 * nebo algoritmus, ktery nejakym zpusobem nemusi byt uplne ten nejlepsi.
 *
 * Prakticka ukazka toho, jak se i jednoduchy ukol da zprasit.
 *
 * Pokuste se zoptimalizovat beh programu tak, abyste usetrili alespon 25 %
 * casu. Efektivita je samozrejme tesne vazana na hardware a architekturu, ale
 * minimalne 25 % casu se da usporit na drtive vetsine prostredi.
 *
 * Regiony k optimalizaci jsou oznaceny komentarovymi bloky BEGIN a END
 *
 * Hinty, co muzete zavest nebo zlepsit:
 * - const, constexpr, pristupy do STL, reference, paralelismus, optimalizace
 * cyklu
 * - datove typy, organizace v pameti, sablony
 * - zjistit, zda je vubec potreba ukladat urcita data
 * - volitelne muzete pouzit profiler
 *
 * Nejprve si sem zapiste referencni cas z prvniho behu: 1470 ms
 * Sem pak zapiste cas, ktery jste obdrzeli po zefektivneni: 156 ms
 */

// BEGIN: Tady dle potreby muzete neco zmenit

// "propracovane" protoze jsem to napsal už pro semestralku z UPG

/// @param span: a span containing target elements
/// @param functor: your function processing a single item from the span.
///
/// Spawns just enough threads to to fully utilize the CPU and distributes
/// the work among them.
///
/// @safety Each thread only recieves it's own disjuncts subspan of the input,
/// but it's up to the user provided function to not access elements outside of
/// that range, or to not invalidate any references, pointers, etc.
template <typename T>
void for_each(const std::span<T> span,
              std::function<void(const size_t index, T &value)> functor) {
  size_t thread_count_hint = std::thread::hardware_concurrency();
  size_t thread_count = thread_count_hint == 0 ? 4 : thread_count_hint;

  size_t batch_size = span.size() / thread_count;

  // Multithread execution
  auto threads = std::views::iota(0uz, thread_count) |
                 std::views::transform([&](auto i) {
                   return std::jthread(
                       [&span, &functor, start = i * batch_size, batch_size]() {
                         for (auto i = start; i < start + batch_size; ++i) {
                           functor(i, span[i]);
                         }
                       });
                 }) |
                 std::ranges::to<std::vector>();

  // Handle the remaining elements
  size_t start = thread_count * batch_size;
  for (T &item : span.subspan(start))
    functor(start++, item);

  // jthreads are automatically awaited at the end of the scope
}

// pocet vstupnich cisel
constexpr size_t inputs_size = 1'000'000;
// minimalni generovane cislo
constexpr int minnum = 1;
// maximalni generovane cislo
constexpr int maxnum = 1000;

// pocet prubehu experimentu
constexpr size_t experiment_run_count = 5;

// vysledna mapa delitelu
std::vector<std::atomic<size_t>> divisors_map(maxnum + 1);

// proved experiment!
void Do_Experiment(std::vector<int> inputs) {
  // vycistime mapu delitelu
  std::ranges::fill(divisors_map, 0);

  for_each<int>(std::span(inputs), [](size_t, auto input) {
    for (auto n : std::views::iota(std::max(2, minnum), maxnum + 1))
      if (input % n == 0)
        divisors_map[n].fetch_add(1, std::memory_order_relaxed);
  });
}
// END: az sem

// Vnitrek funkce main nemente! Vyjimkou je jeden oznaceny blok nize
int main() {
  std::vector<int> randomInputs;

  // nagenerovane vstupy
  randomInputs.reserve(inputs_size);
  std::random_device rdev;
  std::default_random_engine reng(rdev());
  std::uniform_int_distribution<int> rdist(minnum, maxnum);

  for (size_t i = 0; i < inputs_size; i++)
    randomInputs.push_back(rdist(reng));

  // jeden "dry run" kvuli cache a tak podobne
  Do_Experiment(randomInputs);

  auto tp_start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < experiment_run_count; i++)
    Do_Experiment(randomInputs);

  auto tp_end = std::chrono::high_resolution_clock::now();
  auto diff =
      std::chrono::duration_cast<std::chrono::milliseconds>(tp_end - tp_start);

  auto totaltime = diff.count() / experiment_run_count;

  // BEGIN: Tady dle potreby muzete neco zmenit
  for (auto [n, divs] : divisors_map | std::views::enumerate) {
    if (divs > 0)
      std::cout << n << " - " << divs << " delitelu" << std::endl;
  }
  // END: az sem

  std::cout << "Prumerny cas: " << totaltime << "ms" << std::endl;

  return 0;
}
