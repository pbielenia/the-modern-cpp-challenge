#include "solution.hpp"

namespace solution {

unsigned GcdResursive(unsigned a, unsigned b) {
  auto c = a % b;

  if (c == 0)
    return b;
  else
    return GcdResursive(b, c);
}

unsigned GcdIterative(unsigned a, unsigned b) {
  unsigned c{0};

  do {
    c = a % b;
    a = b;
    b = c;
  } while (c != 0);

  return a;
}

}  // namespace solution
