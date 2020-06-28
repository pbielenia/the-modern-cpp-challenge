#include "sexy_prime_pairs/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

using namespace testing;

TEST(GetSexyPairs, ReturnsCorrectFrom15) {
  ASSERT_THAT(get_sexy_pairs(15), ElementsAre(Pair(5, 11), Pair(7, 13)));
}

TEST(GetSexyPairs, ReturnsCorrectFrom100) {
  ASSERT_THAT(get_sexy_pairs(100),
              ElementsAre(Pair(5, 11), Pair(7, 13), Pair(11, 17), Pair(13, 19),
                          Pair(17, 23), Pair(23, 29), Pair(31, 37),
                          Pair(37, 43), Pair(41, 47), Pair(47, 53),
                          Pair(53, 59), Pair(61, 67), Pair(67, 73),
                          Pair(73, 79), Pair(83, 89)));
}
