#pragma once

#include <cinttypes>
#include <map>
#include <string>
#include <vector>

class StrToBinConverter {
public:
    StrToBinConverter() = delete;
    static std::vector<unsigned char> convert(const std::string& hexstring);

private:
    static std::uint8_t to_hex(unsigned char);
};
