#include "least_common_multiple/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

using namespace testing;

TEST(LcmUsingGcd, ReturnsCorrectFrom5And7) {
  ASSERT_THAT(lcm_using_gcd(5, 7), std::lcm(5, 7));
}

TEST(LcmUsingGcd, ReturnsCorrectFrom12And21) {
  ASSERT_THAT(lcm_using_gcd(12, 21), std::lcm(12, 21));
}

TEST(LcmUsingGcd, ReturnsCorrectFrom78And51) {
  ASSERT_THAT(lcm_using_gcd(78, 51), std::lcm(78, 51));
}

TEST(Iterative, ReturnsCorrectFrom5And7) {
  ASSERT_THAT(lcm_iterative(5, 7), std::lcm(5, 7));
}

TEST(Iterative, ReturnsCorrectFrom12And21) {
  ASSERT_THAT(lcm_iterative(12, 21), std::lcm(12, 21));
}

TEST(Iterative, ReturnsCorrectFrom78And51) {
  ASSERT_THAT(lcm_iterative(78, 51), std::lcm(78, 51));
}

TEST(Recursive, ReturnsCorrectFrom5And7) {
  ASSERT_THAT(lcm_recursive(5, 7), std::lcm(5, 7));
}

TEST(Recursive, ReturnsCorrectFrom12And21) {
  ASSERT_THAT(lcm_recursive(12, 21), std::lcm(12, 21));
}

TEST(Recursive, ReturnsCorrectFrom78And51) {
  ASSERT_THAT(lcm_recursive(78, 51), std::lcm(78, 51));
}
