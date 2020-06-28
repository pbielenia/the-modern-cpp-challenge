#include "greatest_common_divisor/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

using namespace testing;

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom5And7) {
  ASSERT_THAT(gcd_recursive(5, 7), std::gcd(5, 7));
}

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom10And20) {
  ASSERT_THAT(gcd_recursive(10, 20), std::gcd(10, 20));
}

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom78And12) {
  ASSERT_THAT(gcd_recursive(78, 12), std::gcd(78, 12));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom5And7) {
  ASSERT_THAT(gcd_iterative(5, 7), std::gcd(5, 7));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom10And20) {
  ASSERT_THAT(gcd_iterative(10, 20), std::gcd(10, 20));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom78And12) {
  ASSERT_THAT(gcd_iterative(78, 12), std::gcd(78, 12));
}
