#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
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

template <std::size_t Size>
std::optional<std::array<std::string_view, Size>> SplitString(
    std::string_view string, char delimiter) {
  std::array<std::string_view, Size> parts;
  std::size_t last_part_end = 0;

  const auto delimiter_count = std::ranges::count(string, delimiter);
  if (delimiter_count != Size - 1) {
    return std::nullopt;
  }

  for (std::size_t index = 0; index < Size; ++index) {
    const auto current_part_start = index == 0 ? 0 : last_part_end + 1;
    const auto current_part_end = string.find(delimiter, current_part_start);

    // Disallow empty parts.
    if (current_part_start == current_part_end ||
        current_part_start == string.size()) {
      return std::nullopt;
    }

    // Valid part.
    if (current_part_end != std::string_view::npos) {
      parts[index] = string.substr(current_part_start,
                                   current_part_end - current_part_start);
      last_part_end = current_part_end;
      continue;
    }

    // Last part.
    if (index == Size - 1) {
      parts[index] = string.substr(current_part_start);
      break;
    }

    // Premature end.
    return std::nullopt;
  }

  return parts;
}

}  // namespace solution