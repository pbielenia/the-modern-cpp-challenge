#include "abundant_numbers/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

TEST(GetProperDivisors, ReturnsCorrectFrom10) {
  ASSERT_THAT(get_proper_divisors(10), ElementsAre(2, 5));
}

TEST(GetProperDivisors, ReturnsCorrectFrom20) {
  ASSERT_THAT(get_proper_divisors(20), ElementsAre(2, 4, 5, 10));
}

TEST(CalculateAbundants, ReturnsCorrectFrom10) {
  ASSERT_THAT(calculate_abundants(10), IsEmpty());
}

TEST(CalculateAbundants, ReturnsCorrectFrom20) {
  ASSERT_THAT(calculate_abundants(20),
              ElementsAre(Pair(12, 3), Pair(18, 2), Pair(20, 1)));
}
