#include "mpnumber.hpp"
#include <cstddef>
#include <deque>
#include <ostream>
#include <ranges>
#include <sstream>
#include <string>

template <const size_t precision> class Calculator {
public:
  MPInt<precision> evaluate(const std::string &expression) {
    std::istringstream iss(expression);

    MPInt<precision> num1, num2, result;

    num1 = parse_number(iss);

    char op;
    iss >> op;

    switch (op) {
    case '+':
      num2 = parse_number(iss);
      result = MPInt<precision>(num1) + MPInt<precision>(num2);
      break;
    case '-':
      num2 = parse_number(iss);
      result = MPInt<precision>(num1) - MPInt<precision>(num2);
      break;
    case '*':
      num2 = parse_number(iss);
      result = MPInt<precision>(num1) * MPInt<precision>(num2);
      break;
    case '/':
      num2 = parse_number(iss);
      result = MPInt<precision>(num1) / MPInt<precision>(num2);
      break;
    case '!':
      result = MPInt<precision>(num1).factorial();
      break;
    default:
      throw std::invalid_argument("Unsupported operation");
    }

    if (bank.size() >= 5) {
      bank.pop_back();
    }
    bank.push_front(result);

    return result;
  };

  void print_bank(std::ostream &out) const {
    for (const auto [i, number] : bank | std::views::enumerate) {
      out << "$" << i + 1 << " = " << number << std::endl;
    }
  }

private:
  std::deque<MPInt<precision>> bank;

  MPInt<precision> parse_number(std::istream &in) {
    char c;
    in >> c;

    if (c == '$') {
      int index;
      in >> index;
      index--;
      if (index < 0 || index >= bank.size()) {
        throw std::invalid_argument("Invalid variable index");
      }
      return bank[index];
    } else {
      in.putback(c);
    }

    std::string buffer;
    while (in >> c) {
      if (std::isdigit(c)) {
        buffer += c;
      } else {
        in.putback(c);
        break;
      }
    }

    if (buffer.empty()) {
      throw std::invalid_argument("Invalid number");
    }

    return MPInt<precision>{std::stoul(buffer)};
  }
};
