#pragma once

#include <cmath>
#include <numeric>

int lcm_iterative(int a, int b);
int lcm_recursive(int const a, int const b, unsigned counter = 1);
int lcm_using_gcd(int a, int b);

// template<class InputIter> int lcmr(InputIter first, InputIter last)
// {
//     return std::accumulate(first, last, 1,
//                            static_cast<int (*)(int, int)>(&lcm_iterative));
// }
