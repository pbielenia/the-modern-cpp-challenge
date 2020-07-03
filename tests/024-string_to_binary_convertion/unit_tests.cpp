#include "string_to_binary_convertion/StrToBinConverter.hpp"

#include <gmock/gmock.h>

using namespace testing;

TEST(StrToBinConverter, ReturnsCorrectFromUppercaseHexString)
{
    ASSERT_THAT(StrToBinConverter::convert("BAADFOOD"),
                ElementsAre(0xBA, 0xAD, 0xF0, 0x0D));
}

TEST(DISABLED_StrToBinConverter, ReturnsCorrectFromLowercaseHexString)
{
    ASSERT_THAT(StrToBinConverter::convert("baadfood"),
                ElementsAre(0xBA, 0xAD, 0xF0, 0x0D));
}
