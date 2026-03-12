#include "ipv4_address.hpp"

#include <charconv>

namespace solution {

namespace {

namespace defaults {

constexpr unsigned kIPv4PartsCount{4};
constexpr char kDotDelimiter{'.'};
constexpr unsigned kMaxAddressLength{15};  // xxx.xxx.xxx.xxx
constexpr std::string_view kInvalidAddressString = "<invalid>";

}  // namespace defaults

/**
 * @brief Splits `input` into `Size` numeric elements separated by
 *        `delimiter`.
 *
 * @tparam Type     Target type of numeric elements.
 * @tparam Size     Target number of numeric elements.
 * @param input     String with `Size` number of elements separated
 *                  by `delimiter`.
 * @param delimiter
 * @return std::optional<std::array<Type, Size>>
 *                  Returns `std::nullopt` if other kind of delimiter is
 *                  encountered or the actual number of output elements does
 *                  not match the expected one.
 */
template <typename Type, unsigned Size>
std::optional<std::array<Type, Size>> SplitStringIntoNumericArray(
    std::string_view string, char delimiter) {
  const auto string_parts = SplitString<Size>(string, delimiter);
  if (!string_parts.has_value()) {
    return std::nullopt;
  }

  std::array<Type, Size> array{};
  for (size_t index = 0; index < Size; ++index) {
    const auto& string_part = string_parts.value().at(index);
    auto result = std::from_chars(string_part.begin(), string_part.end(),
                                  array.at(index));
    if (result.ec != std::errc()) {
      return std::nullopt;
    }
  }

  return array;
}

template <typename Type, unsigned Size>
std::optional<std::string> MakeStringFromNumericArray(
    const std::array<Type, Size>& array,
    unsigned max_string_size,
    char delimiter) {
  std::string string;
  string.resize(max_string_size);

  auto* previous_end = string.data();
  for (unsigned index = 0U; index < Size; ++index) {
    auto result = std::to_chars(previous_end, string.data() + string.size(),
                                array.at(index));
    if (result.ec != std::errc()) {
      return std::nullopt;
    }
    *result.ptr = delimiter;
    previous_end = ++result.ptr;
  }

  string.resize(previous_end - string.data() - 1);
  return string;
}

}  // namespace

IPv4Address::IPv4Address(AddressArray address) : address_{address} {}

std::string IPv4Address::ToString() const {
  return MakeStringFromNumericArray<std::uint8_t, defaults::kIPv4PartsCount>(
             this->address_, defaults::kMaxAddressLength,
             defaults::kDotDelimiter)
      .value_or(std::string(defaults::kInvalidAddressString));
}

std::optional<IPv4Address> MakeIPv4Address(std::string_view address) {
  const auto address_array =
      SplitStringIntoNumericArray<std::uint8_t, defaults::kIPv4PartsCount>(
          address, defaults::kDotDelimiter);
  return address_array.has_value()
             ? std::make_optional(IPv4Address{address_array.value()})
             : std::nullopt;
}

std::ostream& operator<<(std::ostream& stream,
                         const IPv4Address& ipv4_address) {
  stream << ipv4_address.ToString();
  return stream;
}

bool operator==(const IPv4Address& lhs, const IPv4Address& rhs) {
  for (auto index = 0U; index < defaults::kIPv4PartsCount; ++index) {
    if (lhs.address_.at(index) != rhs.address_.at(index)) {
      return false;
    }
  }
  return true;
}

bool operator!=(const IPv4Address& lhs, const IPv4Address& rhs) {
  return !(lhs == rhs);
}

bool operator<(const IPv4Address& lhs, const IPv4Address& rhs) {
  for (size_t index = 0; index < defaults::kIPv4PartsCount; ++index) {
    if (lhs.address_.at(index) < rhs.address_.at(index)) {
      return true;
    }
    if (lhs.address_.at(index) > rhs.address_.at(index)) {
      return false;
    }
  }
  return false;
}

bool operator>(const IPv4Address& lhs, const IPv4Address& rhs) {
  return !(lhs < rhs) && lhs != rhs;
}

}  // namespace solution
