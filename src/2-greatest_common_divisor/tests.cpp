#include <numeric>
#include <gmock/gmock.h>
#include "solution.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace testing;

TEST(Problem1, RecursiveReturnsCorrectFrom5And7) {
    ASSERT_THAT(gcd_recursive(5, 7), std::gcd(5, 7));
}

TEST(Problem1, RecursiveReturnsCorrectFrom10And20) {
    ASSERT_THAT(gcd_recursive(10, 20), std::gcd(10, 20));
}

TEST(Problem1, RecursiveReturnsCorrectFrom78And12) {
    ASSERT_THAT(gcd_recursive(78, 12), std::gcd(78, 12));
}

TEST(Problem1, IterativeReturnsCorrectFrom5And7) {
    ASSERT_THAT(gcd_iterative(5, 7), std::gcd(5, 7));
}

TEST(Problem1, IterativeReturnsCorrectFrom10And20) {
    ASSERT_THAT(gcd_iterative(10, 20), std::gcd(10, 20));
}

TEST(Problem1, IterativeReturnsCorrectFrom78And12) {
    ASSERT_THAT(gcd_iterative(78, 12), std::gcd(78, 12));
}
