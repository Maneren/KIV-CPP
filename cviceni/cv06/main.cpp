#include <array>
#include <format>
#include <print>
#include <utility>

template <const std::size_t DIMENSION, typename T = float,
          typename std::enable_if_t<(DIMENSION >= 2), void> * = nullptr>
class Vector {
public:
  std::array<T, DIMENSION> data;

  Vector() = default;
  Vector(const std::array<T, DIMENSION> &val) : data{val} {}

  // copy konstruktor
  Vector(const Vector &other) : data(other.data) {};

  // move konstruktor
  Vector(Vector &&other) : data(other.data) { other.data.fill(T{}); };

  // copy assignment operator
  Vector &operator=(const Vector &other) {
    this->data = other.data;
    return *this;
  };

  // move assignment operator
  Vector &operator=(Vector &&other) {
    this->data = std::move(other.data);
    other.data.fill(T{});
    return *this;
  };

  // destructor
  ~Vector() = default;

  // shortcut for convenience
  template <typename... E> Vector(E... e) : data{{std::forward<E>(e)...}} {}

  Vector operator+(const Vector &v) const {
    Vector sum{};
    for (std::size_t i = 0; i < DIMENSION; i++) {
      sum.data[i] = data[i] + v.data[i];
    }
    return sum;
  }
  Vector operator+=(const Vector &v) {
    for (std::size_t i = 0; i < DIMENSION; i++) {
      data[i] += v.data[i];
    }
    return *this;
  }

  Vector operator-(const Vector &v) const {
    Vector diff{};
    for (std::size_t i = 0; i < DIMENSION; i++) {
      diff.data[i] = data[i] - v.data[i];
    }
    return diff;
  };
  Vector operator-=(const Vector &v) {
    for (std::size_t i = 0; i < DIMENSION; i++) {
      data[i] -= v.data[i];
    }
    return *this;
  }
};

template <const std::size_t DIMENSION, typename T>
struct std::formatter<Vector<DIMENSION, T>> {
  constexpr auto parse(const std::format_parse_context &ctx) const {
    return ctx.begin();
  }
  auto format(const Vector<DIMENSION, T> &vec, std::format_context &ctx) const {
    std::format_to(ctx.out(), "(");
    std::format_to(ctx.out(), "{}", vec.data[0]);
    for (std::size_t i = 1; i < DIMENSION; i++) {
      std::format_to(ctx.out(), ", {}", vec.data[i]);
    }
    std::format_to(ctx.out(), ")");
    return ctx.out();
  }
};

int main() {
  Vector<2> a{1.f, 2.f};
  Vector<2> b{3.f, 4.f};

  auto c = a + b;
  std::println("{}", c);

  auto a_ = a;

  std::println("{} {}", a, a_);

  auto b_ = std::move(b);

  std::println("{} {}", b, b_);

  Vector<3, int> d{1, 2, 3};
  Vector<3, int> e{4, 5};

  Vector<3, int> d_{d};
  Vector<3, int> e_{std::move(e)};

  std::println("{} {}", d, e);
  std::println("{} {}", d_, e_);

  // Nezkompiluje se
  // Vector<1> f{1.f};
  //
  // std::println("{}", f);

  // Funguje i se stringem :D
  Vector<2, std::string> g{"Hello", "Hi"};
  Vector<2, std::string> h{" ", " "};
  Vector<2, std::string> j{"world", "there"};

  std::println("{}", g + h + j);
}
