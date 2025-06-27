#include "ipv4_address.hpp"

#include <charconv>

namespace solution {

namespace defaults {
constexpr unsigned ipv4_parts_number{4};
constexpr char dot_delimiter{'.'};
constexpr unsigned max_address_length{15};  // xxx.xxx.xxx.xxx
constexpr char invalid_address_string[] = "<invalid>";
}  // namespace defaults

namespace {

/**
 * @brief Splits `input` into `Size` numeric elements separated by `delimiter`.
 *
 * @tparam Type     Target type of numeric elements.
 * @tparam Size     Target number of numeric elements.
 * @param input     String with `Size` number of elements separated
 *                  by `delimiter`.
 * @param delimiter
 * @return std::optional<std::array<Type, Size>>
 *                  Returns `std::nullopt` if other kind of delimiter is
 *                  encountered or the actual number of output elements does not
 *                  match the expected one.
 */
template <typename Type, unsigned Size>
std::optional<std::array<Type, Size>> SplitStringIntoNumericArray(
    std::string_view string,
    char delimiter) {
  std::array<Type, Size> array;

  auto* previous_end = string.begin();
  for (unsigned index = 0; index < Size; ++index) {
    auto result = std::from_chars(previous_end, string.end(), array.at(index));
    if (result.ec != std::errc()) {
      return std::nullopt;
    }
    if (*result.ptr != delimiter && result.ptr != string.end()) {
      return std::nullopt;
    }
    previous_end = ++result.ptr;
  }

  // `previous_end - 1` here points at the last processed character.
  if ((previous_end - 1) != string.end()) {
    return std::nullopt;
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

IPv4Address::IPv4Address(AddressArray address) : address_{std::move(address)} {}

std::string IPv4Address::ToString() const {
  return MakeStringFromNumericArray<std::uint8_t, defaults::ipv4_parts_number>(
             this->address_, defaults::max_address_length,
             defaults::dot_delimiter)
      .value_or(defaults::invalid_address_string);
}

std::optional<IPv4Address> MakeIPv4Address(std::string_view address) {
  auto address_array =
      SplitStringIntoNumericArray<std::uint8_t, defaults::ipv4_parts_number>(
          address, defaults::dot_delimiter);

  if (address_array.has_value()) {
    return IPv4Address{std::move(address_array.value())};
  } else {
    return std::nullopt;
  }
}

std::ostream& operator<<(std::ostream& stream,
                         const IPv4Address& ipv4_address) {
  stream << ipv4_address.ToString();
  return stream;
}

bool operator==(const IPv4Address& lhs, const IPv4Address& rhs) {
  for (auto index = 0U; index < defaults::ipv4_parts_number; ++index) {
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
  for (auto index = 0U; index < defaults::ipv4_parts_number; ++index) {
    if (lhs.address_.at(index) < rhs.address_.at(index)) {
      return true;
    }
  }
  return false;
}

bool operator>(const IPv4Address& lhs, const IPv4Address& rhs) {
  for (auto index = 0U; index < defaults::ipv4_parts_number; ++index) {
    if (lhs.address_.at(index) > rhs.address_.at(index)) {
      return true;
    }
  }
  return false;
}

}  // namespace solution
