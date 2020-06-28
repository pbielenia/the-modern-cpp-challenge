#include "armstrong_numbers/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

TEST(GenerateArmstrongNumbers, ReturnsCorrect) {
  ASSERT_THAT(generate_armstrong_numbers<unsigned short>(),
              ElementsAre(153, 370, 371, 407));
}
