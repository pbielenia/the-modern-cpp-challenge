#include "BinToStrConverter.hpp"

#include <array>
#include <gmock/gmock.h>
#include <vector>

using namespace testing;

TEST(BinToStrConverter, ReturnsUppercaseFromVector)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data, BinToStrConverter::Uppercase).c_str(),
                 "BAADF00D");
}

TEST(BinToStrConverter, ReturnsLowercaseFromHexVector)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data, BinToStrConverter::Lowercase).c_str(),
                 "baadf00d");
}

TEST(BinToStrConverter, ReturnsLowercaseFromHexVectorByDefault)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data).c_str(), "baadf00d");
}

TEST(BinToStrConverter, ReturnsZeroFilledNumbersFromIntArray)
{
    std::array<unsigned char, 6> data{1, 2, 3, 4, 5, 6};
    ASSERT_STREQ(BinToStrConverter::convert(data).c_str(), "010203040506");
}

TEST(BinToStrConverter, ReturnsNumbersFromPOD)
{
    unsigned char data[] = {0x11, 0x22, 0x33, 0x44, 0x55};
    ASSERT_STREQ(BinToStrConverter::convert(data).c_str(), "1122334455");
}
