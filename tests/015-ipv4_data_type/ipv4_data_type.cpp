#include "ipv4_data_type/IPv4Address.hpp"
#include <gmock/gmock.h>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

using namespace testing;

TEST(IPv4Address, GetsAddressWithDots) {
  IPv4Address ipv4_address("192.168.9.21");
  ASSERT_STREQ(ipv4_address.to_str().c_str(), "192.168.9.21");
}

TEST(IPv4Address, GetsAddressAsStream) {
  IPv4Address ipv4_address("0.0.0.0");
  std::stringstream address;
  address << "127.0.0.1";
  address >> ipv4_address;
  ASSERT_STREQ(ipv4_address.to_str().c_str(), "127.0.0.1");
}
