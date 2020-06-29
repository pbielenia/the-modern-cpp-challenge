#include "binary_to_string_conversion/BinToStrConverter.hpp"

#include <gmock/gmock.h>
#include <vector>

using namespace testing;

TEST(BinToStrConverter, ReturnsUppercaseFromVector)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data, BinToStrConverter::Uppercase).c_str(),
                 "BAADFOOD");
}

TEST(BinToStrConverter, ReturnsLowercaseFromHexVector)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data, BinToStrConverter::Lowercase).c_str(),
                 "baadfood");
}

TEST(BinToStrConverter, ReturnsLowercaseFromHexVectorByDefault)
{
    std::vector<unsigned char> data{0xBA, 0xAD, 0xF0, 0x0D};
    ASSERT_STREQ(BinToStrConverter::convert(data).c_str(), "baadfood");
}

TEST(DISABLED_BinToStrConverter, ReturnsNumbersFromIntArray) {}

TEST(DISABLED_BinToStrConverter, ReturnsNumbersFromPOD) {}
