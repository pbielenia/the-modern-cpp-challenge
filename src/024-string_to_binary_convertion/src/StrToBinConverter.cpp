#include "string_to_binary_convertion/StrToBinConverter.hpp"

#include <cctype>

std::vector<unsigned char> StrToBinConverter::convert(const std::string& hexstring)
{
    std::vector<unsigned char> result;
    static const unsigned char hex_base = 16;

    if (hexstring.size() % 2 == 0) {
        for (unsigned i = 0; i < hexstring.size(); i += 2) {
            unsigned char integer =
                to_hex(hexstring.at(i)) * hex_base + to_hex(hexstring.at(i + 1));
            result.push_back(integer);
        }
    }

    return result;
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
                                 + "is not hexadecimal");
    }
}