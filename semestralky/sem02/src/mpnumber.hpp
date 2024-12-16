#pragma once
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <print>
#include <ranges>
#include <string>
#include <vector>

namespace MP {
using namespace MP;

using digit = unsigned short;
using double_digit = unsigned int;
using signed_digit = int;

class __MPInt {};

class Exception : public std::runtime_error {
public:
  explicit Exception(const std::string &message, const __MPInt &value)
      : std::runtime_error(message), value(value) {}

private:
  const __MPInt value;
};
} // namespace MP

constexpr size_t __Unlimited = -1uz;
static constexpr size_t maxp(size_t a, size_t b) {
  return (a == __Unlimited || b == __Unlimited) ? __Unlimited : std::max(a, b);
}

template <const size_t precision = 0uz> class MPInt : public MP::__MPInt {
  template <const size_t other_precision> friend class MPInt;

public:
  static const size_t Unlimited = __Unlimited;

  // Default constructor
  MPInt() : data(precision, 0) {}

  // Construct from unsigned long long
  MPInt(size_t value) : data{} {
    for (auto i = 0; i < sizeof(value) / sizeof(MP::digit) && value > 0; i++) {
      data.push_back(static_cast<MP::digit>(value));
      value >>= 8 * sizeof(MP::digit);
    }
    if (data.empty()) {
      data.push_back(0);
    }
  }

  // Destructor
  ~MPInt() = default;

  // Copy constructor
  MPInt(const MPInt &other) : data(other.data) {}

  // Copy assignment operator
  MPInt &operator=(const MPInt &other) {
    data = other.data;
    if (data.size() > precision) {
      data.resize(precision);
    }
    return *this;
  }

  // Move constructor
  MPInt(MPInt &&other) noexcept : data(std::move(other.data)) {}

  // Move assignment operator
  MPInt &operator=(MPInt &&other) noexcept {
    data = std::move(other.data);
    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> operator+(const MPInt<other_precision> &other) const {
    MPInt<max_precision> result{data};
    result += other;
    return result;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> &operator+=(const MPInt<other_precision> &other) {
    MP::double_digit carry = 0;

    if (data.size() < other.data.size()) {
      data.resize(other.data.size());
    }

    for (auto [digit, other_digit] : std::views::zip(data, other.data)) {
      digit = carrying_add(digit, other_digit, carry);
    }

    while (carry && data.size() < max_precision) {
      data.push_back(static_cast<MP::digit>(carry));
      carry >>= 8 * sizeof(MP::digit);
    }

    if (carry) {
      throw MP::Exception("Overflow", *this);
    }

    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> operator-(const MPInt<other_precision> &other) const {
    MPInt<max_precision> result = *this;
    result -= other;
    return result;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<precision> &operator-=(const MPInt<other_precision> &other) {
    if (data.size() < other.data.size()) {
      data.resize(other.data.size());
    }

    MP::signed_digit borrow = 0;
    for (auto [digit, other_digit] : std::views::zip(data, other.data)) {
      digit = borrowing_sub(digit, other_digit, borrow);
    }

    if (borrow) {
      for (auto &digit : std::span(data).subspan(other.data.size())) {
        digit = borrowing_sub(digit, 0, borrow);
        if (!borrow) {
          break;
        }
      }
    }

    if (borrow) {
      throw MP::Exception("Underflow", *this);
    }

    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> operator*(const MPInt<other_precision> &other) const {
    MPInt<max_precision> result = *this;
    result *= other;
    return result;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<precision> &operator*=(const MPInt<other_precision> &other) {
    if (is_zero() || other.is_zero()) {
      this->data = {0};
    }

    if (data.size() < other.data.size()) {
      data.resize(other.data.size());
    }

    MPInt<max_precision> result{0};
    MPInt<max_precision> temp{0};
    temp.data.resize(std::max(data.size(), other.data.size()), 0);

    MP::double_digit carry = 0;
    for (auto [i, digit] : data | std::views::enumerate) {
      temp.zero();
      for (auto [temp_digit, other_digit] :
           std::views::zip(temp.data, other.data)) {
        temp_digit = carrying_mul(digit, other_digit, carry);
      }
      if (i > 0)
        temp <<= MPInt<max_precision>{static_cast<size_t>(i)};
      result += temp;
    }

    while (result.data.size() > max_precision || result.data.back() == 0) {
      result.data.pop_back();
    }

    while (carry && result.data.size() < max_precision) {
      result.data.push_back(static_cast<MP::digit>(carry));
      carry >>= 8 * sizeof(MP::digit);
    }

    *this = result;
    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  std::tuple<MPInt<max_precision> &, MPInt<max_precision>>
  euclid_div(const MPInt<other_precision> &other) {
    if (other.is_zero()) {
      throw std::runtime_error("Divide by zero");
    }

    MPInt<max_precision> result{0};
    MPInt<max_precision> remainder{0};
    MPInt<max_precision> one{1};

    for (auto digit : data | std::views::reverse) {
      result <<= one;
      remainder <<= one;
      remainder += MPInt<max_precision>{digit};

      while (remainder >= other) {
        remainder -= other;
        result += one;
      }
    }

    data = result.data;

    return {*this, remainder};
  }

  template <const size_t other_precision>
  MPInt operator/(const MPInt<other_precision> &other) const {
    MPInt<std::max(precision, other_precision)> temp = *this;
    temp /= other;
    return temp;
  }

  template <const size_t other_precision>
  MPInt<precision> &operator/=(const MPInt<other_precision> &other) {
    if (other.is_zero()) {
      throw std::runtime_error("Divide by zero");
    }

    euclid_div(other);

    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> operator%(const MPInt<other_precision> &other) const {
    MPInt<max_precision> temp = *this;
    temp %= other;
    return temp;
  }

  template <const size_t other_precision>
  MPInt<precision> &operator%=(const MPInt<other_precision> &other) {
    if (other.is_zero()) {
      throw std::runtime_error("Divide by zero");
    }

    auto [_, remainder] = euclid_div(other);

    data = remainder.data;

    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<max_precision> operator<<(const MPInt<other_precision> &other) const {
    MPInt<max_precision> result = *this;
    result <<= other;
    return result;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  MPInt<precision> &operator<<=(const MPInt<other_precision> &other) {
    MPInt<max_precision> result = *this;
    MPInt<max_precision> temp = other;
    MPInt<max_precision> one{1};

    while (!temp.is_zero()) {
      data.insert(data.begin(), 0);
      temp -= one;
    }

    if (data.size() > max_precision) {
      data.resize(precision);
    }

    return *this;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  bool operator>(const MPInt<other_precision> &other) const {
    for (auto i :
         std::views::iota(0uz, std::max(data.size(), other.data.size())) |
             std::views::reverse) {
      if (i >= data.size()) {
        if (other.data[i] > 0)
          return false;
      } else if (i >= other.data.size()) {
        if (data[i] > 0)
          return true;
      } else if (data[i] > other.data[i]) {
        return true;
      } else if (data[i] < other.data[i]) {
        return false;
      }
    }
    return false;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  bool operator<(const MPInt<other_precision> &other) const {
    for (auto i :
         std::views::iota(0uz, std::max(data.size(), other.data.size())) |
             std::views::reverse) {
      if (i >= data.size()) {
        if (other.data[i] > 0)
          return true;
      } else if (i >= other.data.size()) {
        if (data[i] > 0)
          return false;
      } else if (data[i] > other.data[i]) {
        return false;
      } else if (data[i] < other.data[i]) {
        return true;
      }
    }
    return false;
  }

  template <const size_t other_precision,
            const size_t max_precision = maxp(precision, other_precision)>
  bool operator==(const MPInt<other_precision> &other) const {
    for (auto i :
         std::views::iota(0uz, std::max(data.size(), other.data.size())) |
             std::views::reverse) {
      if (i >= data.size()) {
        if (other.data[i] > 0)
          return false;
      } else if (i >= other.data.size()) {
        if (data[i] > 0)
          return false;
      } else if (data[i] != other.data[i]) {
        return false;
      }
    }
    return true;
  }

  template <const size_t other_precision>
  bool operator>=(const MPInt<other_precision> &other) const {
    return *this > other || *this == other;
  }

  template <const size_t other_precision>
  bool operator<=(const MPInt<other_precision> &other) const {
    return *this < other || *this == other;
  }

  bool is_zero() const {
    return std::ranges::all_of(data, [](MP::digit b) { return b == 0; });
  }

  void zero() { std::ranges::fill(data, 0); }

  MPInt<precision> factorial() {
    MPInt<precision> temp{data};
    MPInt<precision> result{1};
    MPInt<precision> one{1};

    while (!temp.is_zero()) {
      result *= temp;
      temp -= one;
    }

    return result;
  }

  friend std::ostream &operator<<(std::ostream &out,
                                  const MPInt<precision> &mpint) {
    if (mpint.is_zero()) {
      out << "0";
      return out;
    }

    std::vector<unsigned char> digits;

    MPInt<precision> temp = mpint;
    MPInt<precision> decimal_factor{10000};

    bool written = false;

    while (!temp.is_zero()) {
      auto [_, rem] = temp.euclid_div(decimal_factor);
      auto last_digit = rem.data[0];

      if (!written && last_digit == 0) {
        digits.push_back('0');
        digits.push_back('0');
        digits.push_back('0');
        digits.push_back('0');
      }

      while (last_digit > 0) {
        MP::digit digit = last_digit % 10;
        last_digit /= 10;
        digits.push_back('0' + digit);
        written = true;
      }
    }

    while (digits.size() > 1 && digits.back() == '0') {
      digits.pop_back();
    }

    for (auto digit : digits | std::views::reverse) {
      out << digit;
    }

    return out;
  }

private:
  std::vector<MP::digit> data;

  MPInt(const std::vector<MP::digit> &data) : data(data) {
    if (data.size() > precision) {
      this->data.resize(precision);
    }
  }

  static constexpr size_t LOG10_DIGIT = 3;

  static MP::digit carrying_add(const MP::digit a, const MP::digit b,
                                MP::double_digit &carry) {
    carry +=
        static_cast<MP::double_digit>(a) + static_cast<MP::double_digit>(b);
    MP::digit lo = carry;
    carry >>= 8 * sizeof(MP::digit);

    return lo;
  }

  static MP::digit borrowing_sub(const MP::digit a, const MP::digit b,
                                 MP::signed_digit &borrow) {
    borrow +=
        static_cast<MP::signed_digit>(a) - static_cast<MP::signed_digit>(b);
    MP::digit positive = static_cast<MP::digit>(borrow);
    borrow >>= 8 * sizeof(MP::digit);

    return positive;
  }

  static MP::digit carrying_mul(MP::digit a, MP::digit b,
                                MP::double_digit &carry) {
    carry +=
        static_cast<MP::double_digit>(a) * static_cast<MP::double_digit>(b);
    MP::digit lo = static_cast<MP::digit>(carry);
    carry >>= 8 * sizeof(MP::digit);

    return lo;
  }
};
