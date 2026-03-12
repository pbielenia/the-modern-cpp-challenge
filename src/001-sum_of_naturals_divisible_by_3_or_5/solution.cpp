#include "solution.hpp"

#include <algorithm>
#include <span>

namespace {

bool NumberIsDivisibleByAnyOf(unsigned number, std::span<const unsigned> divisors) {
  return std::ranges::any_of(divisors, [&number](auto divisor) {
    return divisor != 0 && number % divisor == 0;
  });
}

}  // namespace

namespace solution {

unsigned long long SumOfNaturalsDivisibleByThreeOrFive(unsigned value_limit) {
  static constexpr unsigned kStartValue{3};
  static constexpr std::array<unsigned, 2> kDivisors{3, 5};

  unsigned long long sum{0};
  for (auto number = kStartValue; number <= value_limit; ++number) {
    if (NumberIsDivisibleByAnyOf(number, kDivisors)) {
      sum += number;
    }
  }

  return sum;
}

}  // namespace solution
