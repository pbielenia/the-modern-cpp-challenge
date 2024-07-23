#include "ipv4_address/ipv4_address.hpp"
#include <gmock/gmock.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

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
