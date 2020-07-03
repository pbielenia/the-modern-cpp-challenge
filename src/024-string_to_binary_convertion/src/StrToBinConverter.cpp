#include "string_to_binary_convertion/StrToBinConverter.hpp"

std::vector<unsigned char> StrToBinConverter::convert(const std::string& hexstring)
{
    return std::vector<unsigned char>(hexstring.begin(), hexstring.end());
}
