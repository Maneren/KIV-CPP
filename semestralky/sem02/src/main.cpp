#include "calculator.hpp"
#include "mpnumber.hpp"
#include <iostream>
#include <ostream>

void run_calculator(auto &calculator) {
  std::string command;

  while (true) {
    std::cout << "> ";
    std::cin >> command;

    if (command == "exit" || command == "") {
      break;
    }

    if (command == "bank") {
      calculator.print_bank(std::cout);
    } else {
      try {
        auto result = calculator.evaluate(command);
        std::cout << "$1 = " << result << std::endl;
      } catch (const MP::Exception &e) {
        std::cerr << e.what() << std::endl;
      } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
      }
    }
  }
}

void print_help(char *argv[]) {
  std::cerr << "Usage: " << argv[0] << " <mode>" << std::endl
            << std::endl
            << "Available modes:" << std::endl
            << " 1 - unlimited" << std::endl
            << " 2 - limited to 32 bytes" << std::endl
            << " 3 - demo" << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    print_help(argv);
    return 1;
  }

  auto mode = std::string{argv[1]};

  if (mode == "1") {
    std::cout << "Unlimited precision mode" << std::endl;
    Calculator<MP::Unlimited> calculator;
    run_calculator(calculator);
  } else if (mode == "2") {
    std::cout << "Limited precision mode" << std::endl;
    Calculator<32> calculator;
    run_calculator(calculator);
  } else if (mode == "3") {
    std::cout << "Demo mode" << std::endl;
    MPInt<4> a{10};
    std::cout << "a = " << a << std::endl;
    MPInt<5> b{20};
    std::cout << "b = " << b << std::endl;
    MPInt c = a + b;
    static_assert(c.precision() == 5);
    std::cout << "c = a + b = " << c << std::endl;
    MPInt d = c - b;
    std::cout << "d = c - b = " << d << std::endl;
    MPInt e = b * c;
    std::cout << "e = b * c = " << e << std::endl;
    MPInt f = e / c;
    std::cout << "f = e / c = " << f << std::endl;
    MPInt g = MPInt<MP::Unlimited>{20}.factorial();
    std::cout << "g = 20! = " << g << std::endl;
    MPInt h{3628800};
    std::cout << "h = " << h << std::endl;
    MPInt i = g / h;
    std::cout << "i = g / h = " << i << std::endl;
    MPInt j = MPInt<MP::Unlimited>{100}.factorial();
    std::cout << "j = 100! = " << j << std::endl;
  } else {
    print_help(argv);
    return 1;
  }

  return 0;
}
