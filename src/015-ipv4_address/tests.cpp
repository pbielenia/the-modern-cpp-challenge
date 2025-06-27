#include "ipv4_address.hpp"
#include <gmock/gmock.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

namespace {

TEST(IPv4Address, ConstructsWellFormed) {
  auto ipv4_address = solution::MakeIPv4Address("192.168.9.21");
  ASSERT_TRUE(ipv4_address.has_value());
  EXPECT_STREQ(ipv4_address.value().ToString().c_str(), "192.168.9.21");
}

TEST(IPv4Address, ReturnsNulloptAtAddressOutOfByteRange) {
  auto ipv4_address = solution::MakeIPv4Address("192.168.256.21");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, ReturnsNulloptAtInvalidDelimiter) {
  auto ipv4_address = solution::MakeIPv4Address("192.168/9.21");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, ReturnsNulloptAtAddressTooShort) {
  auto ipv4_address = solution::MakeIPv4Address("192.168.9");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, ReturnsNulloptAtAddressTooLong) {
  auto ipv4_address = solution::MakeIPv4Address("192.168.9.21.50");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, ReturnsNulloptAtAddressStartingWithDelimiter) {
  auto ipv4_address = solution::MakeIPv4Address(".192.168.9.21");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, ReturnsNulloptAtAddressEndingWithDelimiter) {
  auto ipv4_address = solution::MakeIPv4Address("192.168.9.50.");
  EXPECT_FALSE(ipv4_address.has_value());
}

TEST(IPv4Address, SupportsStreamExtractionOperator) {
  auto ipv4_address = solution::IPv4Address({192, 168, 9, 50});
  std::stringstream stream;
  stream << ipv4_address;
  ASSERT_STREQ(stream.str().c_str(), "192.168.9.50");
}

struct CompareOperatorsTestData {
  enum class Comparison { Equal, NotEqual, LessThan, GreaterThan };

  CompareOperatorsTestData() = delete;

  CompareOperatorsTestData(solution::IPv4Address::AddressArray first_array,
                           solution::IPv4Address::AddressArray second_array,
                           Comparison comparison,
                           bool expected_result)
      : first{first_array},
        second{second_array},
        comparison{comparison},
        expected_result{expected_result} {}

  solution::IPv4Address first;
  solution::IPv4Address second;
  Comparison comparison;
  bool expected_result;
};

std::ostream& operator<<(
    std::ostream& stream,
    const CompareOperatorsTestData::Comparison& comparison) {
  switch (comparison) {
    case CompareOperatorsTestData::Comparison::Equal:
      stream << "equal";
      break;
    case CompareOperatorsTestData::Comparison::NotEqual:
      stream << "not equal";
      break;
    case CompareOperatorsTestData::Comparison::LessThan:
      stream << "less than";
      break;
    case CompareOperatorsTestData::Comparison::GreaterThan:
      stream << "greater than";
      break;
  }
  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const CompareOperatorsTestData& data) {
  stream << "{ " << "first: " << data.first << ", second: " << data.second
         << ", comparison: " << data.comparison
         << ", expected_result: " << std::boolalpha << data.expected_result
         << " }";
  return stream;
}

class IPv4AddressCompareOperatorsFixture
    : public TestWithParam<CompareOperatorsTestData> {};

TEST_P(IPv4AddressCompareOperatorsFixture, TestComparisonIsTrue) {
  auto params = GetParam();
  switch (params.comparison) {
    case CompareOperatorsTestData::Comparison::Equal:
      EXPECT_THAT(params.first == params.second, params.expected_result);
      break;
    case CompareOperatorsTestData::Comparison::NotEqual:
      EXPECT_THAT(params.first != params.second, params.expected_result);
      break;
    case CompareOperatorsTestData::Comparison::GreaterThan:
      EXPECT_THAT(params.first > params.second, params.expected_result);
      break;
    case CompareOperatorsTestData::Comparison::LessThan:
      EXPECT_THAT(params.first < params.second, params.expected_result);
      break;
  }
}

INSTANTIATE_TEST_SUITE_P(
    AddressesAreEqualTestSuite,
    IPv4AddressCompareOperatorsFixture,
    Values(CompareOperatorsTestData({0, 0, 0, 0},
                                    {0, 0, 0, 0},
                                    CompareOperatorsTestData::Comparison::Equal,
                                    true),
           CompareOperatorsTestData({255, 255, 255, 255},
                                    {255, 255, 255, 255},
                                    CompareOperatorsTestData::Comparison::Equal,
                                    true),
           CompareOperatorsTestData({192, 168, 9, 50},
                                    {192, 168, 9, 50},
                                    CompareOperatorsTestData::Comparison::Equal,
                                    true)));

INSTANTIATE_TEST_SUITE_P(
    AddressesAreNotEqualTestSuite,
    IPv4AddressCompareOperatorsFixture,
    Values(
        CompareOperatorsTestData({1, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true),
        CompareOperatorsTestData({0, 1, 0, 0},
                                 {0, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true),
        CompareOperatorsTestData({0, 0, 1, 0},
                                 {0, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {0, 0, 0, 1},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true),
        CompareOperatorsTestData({255, 255, 255, 1},
                                 {255, 255, 255, 255},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true),
        CompareOperatorsTestData({192, 168, 1, 50},
                                 {192, 168, 9, 50},
                                 CompareOperatorsTestData::Comparison::NotEqual,
                                 true)));

INSTANTIATE_TEST_SUITE_P(
    AddressIsLessThanTestSuite,
    IPv4AddressCompareOperatorsFixture,
    Values(
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {1, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {0, 1, 0, 0},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {0, 0, 1, 0},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {0, 0, 0, 1},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 2},
                                 {0, 0, 1, 1},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({192, 168, 1, 50},
                                 {192, 168, 9, 50},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 true),
        CompareOperatorsTestData({0, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 false),
        CompareOperatorsTestData({1, 0, 0, 0},
                                 {0, 0, 0, 0},
                                 CompareOperatorsTestData::Comparison::LessThan,
                                 false)));

INSTANTIATE_TEST_SUITE_P(
    AddressIsGreaterThanTestSuite,
    IPv4AddressCompareOperatorsFixture,
    Values(CompareOperatorsTestData(
               {1, 0, 0, 0},
               {0, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {0, 1, 0, 0},
               {0, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {0, 0, 1, 0},
               {0, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {0, 0, 0, 1},
               {0, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {0, 0, 1, 1},
               {0, 0, 0, 2},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {192, 168, 9, 50},
               {192, 168, 1, 50},
               CompareOperatorsTestData::Comparison::GreaterThan,
               true),
           CompareOperatorsTestData(
               {0, 0, 0, 0},
               {0, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               false),
           CompareOperatorsTestData(
               {0, 0, 0, 0},
               {1, 0, 0, 0},
               CompareOperatorsTestData::Comparison::GreaterThan,
               false)));

}  // namespace
