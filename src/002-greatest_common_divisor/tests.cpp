#include <gmock/gmock.h>
#include <numeric>
#include "solution.hpp"

using namespace testing;

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom5And7) {
  ASSERT_THAT(solution::GcdResursive(5, 7), std::gcd(5, 7));
}

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom10And20) {
  ASSERT_THAT(solution::GcdResursive(10, 20), std::gcd(10, 20));
}

TEST(GreatestCommonDivisor, RecursiveReturnsCorrectFrom78And12) {
  ASSERT_THAT(solution::GcdResursive(78, 12), std::gcd(78, 12));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom5And7) {
  ASSERT_THAT(solution::GcdIterative(5, 7), std::gcd(5, 7));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom10And20) {
  ASSERT_THAT(solution::GcdIterative(10, 20), std::gcd(10, 20));
}

TEST(GreatestCommonDivisor, IterativeReturnsCorrectFrom78And12) {
  ASSERT_THAT(solution::GcdIterative(78, 12), std::gcd(78, 12));
}
