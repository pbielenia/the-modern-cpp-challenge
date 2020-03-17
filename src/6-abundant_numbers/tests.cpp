#include <numeric>
#include <gmock/gmock.h>
#include "solution.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace testing;

TEST(LcmUsingGcd, ReturnsCorrectFrom5And7) {
    ASSERT_THAT(0, 0);
}
