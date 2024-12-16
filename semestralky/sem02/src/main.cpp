#include "mpnumber.hpp"
#include <iostream>
#include <ostream>

int main(int argc, char *argv[]) {
  std::cout << sizeof(unsigned long long) << std::endl;
  MPInt<4> a{10};
  std::cout << a << std::endl;
  MPInt<5> b{20};
  std::cout << b << std::endl;
  MPInt c = a + b;
  std::cout << c << std::endl;
  MPInt d = c - b;
  std::cout << d << std::endl;
  MPInt e = b * c;
  std::cout << e << std::endl;
  MPInt f = e / c;
  std::cout << f << std::endl;
  MPInt g = MPInt<MPInt<>::Unlimited>{200}.factorial();
  std::cout << g << std::endl;
  MPInt h{3628800};
  std::cout << h << std::endl;
  MPInt i = g / h;
  std::cout << i << std::endl;
  return 0;
}
