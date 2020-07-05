#pragma once

#include <cinttypes>
#include <map>
#include <string>
#include <vector>

class StrToBinConverter {
public:
    StrToBinConverter() = delete;
    static std::vector<unsigned char> convert(const std::string& hexstring);
    static std::vector<unsigned char> convert(const std::string& hexstring,
                                              char delimiter);

private:
    static std::uint8_t to_hex(unsigned char);
    static unsigned char create_integer(unsigned char, unsigned char);
};
