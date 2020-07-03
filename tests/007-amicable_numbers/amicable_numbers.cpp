#include "amicable_numbers/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

TEST(CalculateAmicables, ReturnsCorrectFrom67000) {
  ASSERT_THAT(calculate_amicables(67000),
              ElementsAre(Pair(220, 284), Pair(1184, 1210), Pair(2620, 2924),
                          Pair(5020, 5564), Pair(6232, 6368),
                          Pair(10744, 10856), Pair(12285, 14595),
                          Pair(17296, 18416), Pair(63020, 76084),
                          Pair(66928, 66992)));
}
