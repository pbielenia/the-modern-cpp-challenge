#include "solution.hpp"

#include <cmath>
#include <numeric>

int lcm_iterative(int a, int b) {
  auto _c = a * b;
  auto _a = a;
  auto _b = b;

  while (_b != 0) {
    auto t = _b;
    _b = _a % _b;
    _a = t;
  }

  return _c / _a;
}

int lcm_recursive(int const a, int const b, unsigned counter) {
  if (((counter % a) == 0) && ((counter % b) == 0))
    return counter;
  return lcm_recursive(a, b, counter + 1);
}

int lcm_using_gcd(int a, int b) {
  return std::abs(a * b) / std::gcd(a, b);
}
