#include <algorithm>
#include <array>
#include <list>
#include <print>
#include <vector>

template <typename T, typename... Args> bool Any_Contains(T t, Args... args) {
  return ((std::ranges::find(args, t) != args.end()) || ...);
}

// jak to udělat hezky jenom pomocí jednoho variadického parametru jsem
// nevymyslel
void Quoted_Print(auto t, auto... args) {
  std::print("\"{}\"", t);
  (std::print(", \"{}\"", args), ...);
}

int main() {
  std::vector<int> a{5, 6, 7, 8};
  std::list<int> b{8, 9, 11};
  std::array<int, 3> c{10, 12, 15};

  if (Any_Contains(10, a, b, c)) {
    std::println("Found!");
  }

  Quoted_Print("ahoj", "C++", 12, 66.6);

  return 0;
}
