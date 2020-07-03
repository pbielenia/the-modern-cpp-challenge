#pragma once

#include <string>
#include <vector>

class StrToBinConverter {
public:
    StrToBinConverter() = delete;
    static std::vector<unsigned char> convert(const std::string& hexstring);

private:
    //
};
