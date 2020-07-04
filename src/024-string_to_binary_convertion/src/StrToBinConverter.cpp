#include "string_to_binary_convertion/StrToBinConverter.hpp"

#include <algorithm>
#include <cctype>
#include <iterator>

std::vector<unsigned char> StrToBinConverter::convert(const std::string& hexstring)
{
    std::vector<unsigned char> result;
    unsigned starting_index = 0;

    if (hexstring.size() > 0 && hexstring.size() % 2 == 0) {
        result.push_back(
            create_integer(to_hex(hexstring.at(0)), to_hex(hexstring.at(1))));
        starting_index = 2;
    } else {
        result.push_back(create_integer(0, to_hex(hexstring.at(0))));
        starting_index = 1;
    }
    for (unsigned i = starting_index; i < hexstring.size(); i += 2) {
        unsigned char integer =
            create_integer(to_hex(hexstring.at(i)), to_hex(hexstring.at(i + 1)));
        result.push_back(integer);
    }

    return result;
}

std::vector<unsigned char> StrToBinConverter::convert(const std::string& hexstring,
                                                      char delimiter)
{
    std::string continous_hexstring;
    std::copy_if(hexstring.begin(), hexstring.end(),
                 std::back_inserter(continous_hexstring),
                 [delimiter](char c) { return c != delimiter; });
    return convert(continous_hexstring);
}

std::uint8_t StrToBinConverter::to_hex(unsigned char hex_char)
{
    static const std::map<unsigned char, unsigned char> hex_bytes{
        {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3}, {'4', 4},  {'5', 5},
        {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9}, {'A', 10}, {'B', 11},
        {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}};

    const auto common_hex_char = std::toupper(hex_char);
    if (hex_bytes.count(common_hex_char)) {
        return hex_bytes.at(common_hex_char);
    } else {
        throw std::runtime_error("Character " + std::to_string(hex_char)
                                 + " is not hexadecimal");
    }
}

unsigned char StrToBinConverter::create_integer(unsigned char higher, unsigned char lower)
{
    static constexpr unsigned char hex_base = 16;
    return higher * hex_base + lower;
}
