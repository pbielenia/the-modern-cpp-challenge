#include <ios>

#include "gtest/gtest.h"

#include "ipv4_address.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

using namespace testing;
using AddressArray = solution::IPv4Address::AddressArray;

struct MakeIpv4AddressTestData {
  std::string input_address;
  std::optional<solution::IPv4Address> expected;
};

class MakeIpv4AddressFixture : public TestWithParam<MakeIpv4AddressTestData> {};

TEST_P(MakeIpv4AddressFixture, Mixed) {
  EXPECT_EQ(solution::MakeIPv4Address(GetParam().input_address),
            GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(MakeIpv4AddressTestSuite,
                         MakeIpv4AddressFixture,
                         Values(
                             MakeIpv4AddressTestData{
                                 "192.168.9.21",
                                 AddressArray{192, 168, 9, 21},
                             },
                             // Value greater than 255
                             MakeIpv4AddressTestData{
                                 "192.168.256.21",
                                 std::nullopt,
                             },
                             // Unexpected character
                             MakeIpv4AddressTestData{
                                 "192.168/9.21",
                                 std::nullopt,
                             },
                             // Begins with delimiter
                             MakeIpv4AddressTestData{
                                 ".192.168.9.21",
                                 std::nullopt,
                             },
                             // Ends with delimiter
                             MakeIpv4AddressTestData{
                                 "192.168.9.21.",
                                 std::nullopt,
                             },
                             // Address too short
                             MakeIpv4AddressTestData{
                                 "192.168.9",
                                 std::nullopt,
                             },
                             // Address too long
                             MakeIpv4AddressTestData{
                                 "192.168.9.21.50",
                                 std::nullopt,
                             }));

TEST(IPv4Address, SupportsStreamExtractionOperator) {
  auto ipv4_address = solution::IPv4Address({192, 168, 9, 50});
  std::stringstream stream;
  stream << ipv4_address;
  ASSERT_STREQ(stream.str().c_str(), "192.168.9.50");
}

struct CompareOperatorsTestData {
  struct Results {
    bool less_than = false;
    bool equal_to = false;
    bool not_equal_to = false;
    bool greater_than = false;
  };

  solution::IPv4Address lhs;
  solution::IPv4Address rhs;
  Results expected;
};

constexpr auto kExpectedForLess = CompareOperatorsTestData::Results{
    .less_than = true,
    .equal_to = false,
    .not_equal_to = true,
    .greater_than = false,
};
constexpr auto kExpectedForEqual = CompareOperatorsTestData::Results{
    .less_than = false,
    .equal_to = true,
    .not_equal_to = false,
    .greater_than = false,
};
constexpr auto kExpectedForGreater = CompareOperatorsTestData::Results{
    .less_than = false,
    .equal_to = false,
    .not_equal_to = true,
    .greater_than = true,
};

std::ostream& operator<<(std::ostream& stream,
                         const CompareOperatorsTestData::Results& results) {
  stream << std::boolalpha << "{ less_than: " << results.less_than
         << ", equal_to: " << results.equal_to
         << ", not_equal_to: " << results.not_equal_to
         << ", greater_than: " << results.greater_than << " }";
  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const CompareOperatorsTestData& data) {
  stream << "{ " << "lhs: " << data.lhs << ", rhs: " << data.rhs
         << ", expected: " << data.expected << " }";
  return stream;
}

class CompareOperatorsFixture : public TestWithParam<CompareOperatorsTestData> {
};

TEST_P(CompareOperatorsFixture, Mixed) {
  EXPECT_EQ(GetParam().lhs < GetParam().rhs, GetParam().expected.less_than);
  EXPECT_EQ(GetParam().lhs == GetParam().rhs, GetParam().expected.equal_to);
  EXPECT_EQ(GetParam().lhs != GetParam().rhs, GetParam().expected.not_equal_to);
  EXPECT_EQ(GetParam().lhs > GetParam().rhs, GetParam().expected.greater_than);
}

INSTANTIATE_TEST_SUITE_P(CompareOperatorsTestSuite,
                         CompareOperatorsFixture,
                         Values(
                             CompareOperatorsTestData{
                                 AddressArray{255, 255, 255, 1},
                                 AddressArray{255, 255, 255, 255},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{192, 168, 1, 50},
                                 AddressArray{192, 168, 9, 50},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 0},
                                 AddressArray{1, 0, 0, 0},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 0},
                                 AddressArray{0, 1, 0, 0},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 0},
                                 AddressArray{0, 0, 1, 0},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 0},
                                 AddressArray{0, 0, 0, 1},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 2},
                                 AddressArray{0, 0, 1, 1},
                                 kExpectedForLess,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 0},
                                 AddressArray{0, 0, 0, 0},
                                 kExpectedForEqual,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{255, 255, 255, 255},
                                 AddressArray{255, 255, 255, 255},
                                 kExpectedForEqual,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{192, 168, 9, 50},
                                 AddressArray{192, 168, 9, 50},
                                 kExpectedForEqual,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{1, 0, 0, 0},
                                 AddressArray{0, 0, 0, 0},
                                 kExpectedForGreater,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 1, 0, 0},
                                 AddressArray{0, 0, 0, 0},
                                 kExpectedForGreater,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 1, 0},
                                 AddressArray{0, 0, 0, 0},
                                 kExpectedForGreater,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 0, 1},
                                 AddressArray{0, 0, 0, 0},
                                 kExpectedForGreater,
                             },
                             CompareOperatorsTestData{
                                 AddressArray{0, 0, 1, 1},
                                 AddressArray{0, 0, 0, 2},
                                 kExpectedForGreater,
                             }));
}  // namespace
