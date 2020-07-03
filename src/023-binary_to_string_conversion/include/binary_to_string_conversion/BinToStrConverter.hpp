#pragma once

#include <iomanip>
#include <sstream>
#include <string>

class BinToStrConverter {
public:
    enum LettersCase { Lowercase, Uppercase };

    template<typename T>
    static std::string convert(const T& data, LettersCase letters_case = Lowercase)
    {
        std::ostringstream converted;
        if (letters_case == Uppercase) {
            converted << std::uppercase;
        }

        for (const auto elem : data) {
            converted << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(elem);
        }
        return converted.str();
    }
};
