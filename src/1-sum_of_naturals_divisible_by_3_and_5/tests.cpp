#include <gmock/gmock.h>
#include "solution.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

using namespace testing;

TEST(BarTest, Exists) {
    ASSERT_THAT(returns_zero(), Eq(3));
}
