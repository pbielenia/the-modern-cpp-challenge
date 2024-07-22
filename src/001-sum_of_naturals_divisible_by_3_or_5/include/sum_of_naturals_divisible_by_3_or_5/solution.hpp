#pragma once

namespace solution {

bool NumberIsDivisible(unsigned number, unsigned divider) {
  return (number % divider) == 0;
}

// Returns the sum of all natural numbers divisible by 3 OR 5, up to the
// `value_limit`.
unsigned long long SumOfNaturalsDivisibleByThreeOrFive(unsigned value_limit) {
  static unsigned start_value{3};

  unsigned long long sum{0};

  for (auto number = start_value; number <= value_limit; ++number) {
    if (NumberIsDivisible(number, 3) || NumberIsDivisible(number, 5)) {
      sum += number;
    }
  }

  return sum;
}

}  // namespace solution
