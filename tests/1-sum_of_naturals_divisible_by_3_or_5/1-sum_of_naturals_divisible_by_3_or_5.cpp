#include "1-sum_of_naturals_divisible_by_3_or_5/solution.hpp"
#include <gmock/gmock.h>

using namespace testing;

TEST(Problem1, Returns0When0Passed) {
  ASSERT_THAT(sum_of_naturals_divisible_by_3_or_5(0), Eq(0));
}

TEST(Problem1, Returns3When3Passed) {
  ASSERT_THAT(sum_of_naturals_divisible_by_3_or_5(3), Eq(3));
}

TEST(Problem1, Returns8When5Passed) {
  ASSERT_THAT(sum_of_naturals_divisible_by_3_or_5(5), Eq(8));
}

TEST(Problem1, Returns33When10Passed) {
  ASSERT_THAT(sum_of_naturals_divisible_by_3_or_5(10), Eq(33));
}

TEST(Problem1, Returns98When20Passed) {
  ASSERT_THAT(sum_of_naturals_divisible_by_3_or_5(20), Eq(98));
}
