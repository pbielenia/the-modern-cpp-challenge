#pragma once

#include <array>
#include <cstdint>
#include <optional>
#include <string>

namespace solution {

class IPv4Address {
 public:
  using AddressArray = std::array<std::uint8_t, 4U>;
  /**
   * @brief Construct a new IPv4Address object
   *
   * @param address
   */
  IPv4Address(AddressArray address);

  std::string ToString() const;

  friend bool operator==(const IPv4Address&, const IPv4Address&);
  friend bool operator!=(const IPv4Address&, const IPv4Address&);
  friend bool operator<(const IPv4Address&, const IPv4Address&);
  friend bool operator>(const IPv4Address&, const IPv4Address&);

 private:
  AddressArray address_;
};

/**
 *  @brief Constructs a new IPv4Address object
 *
 *  @param address Address from which IPv4Address will be created.
 *                 E.g. "127.0.0.1" or "168.192.0.100".
 *
 *  @return std::nullopt if the `address` can not be parsed.
 */
std::optional<IPv4Address> MakeIPv4Address(std::string_view address);

std::ostream& operator<<(std::ostream&, const IPv4Address&);

bool operator==(const IPv4Address& lhs, const IPv4Address& rhs);
bool operator!=(const IPv4Address& lhs, const IPv4Address& rhs);
bool operator<(const IPv4Address& lhs, const IPv4Address& rhs);
bool operator>(const IPv4Address& lhs, const IPv4Address& rhs);

}  // namespace solution