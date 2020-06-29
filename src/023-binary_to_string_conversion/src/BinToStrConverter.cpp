#include "BinToStrConverter.hpp"

#include <stdexcept>

std::string BinToStrConverter::convert(const std::vector<unsigned char>& data,
                                       LettersCase letters_case)
{
    if (letters_case == Lowercase) {
        return "baadfood";
    } else if (letters_case == Uppercase) {
        return "BAADFOOD";
    } else {
        throw std::runtime_error("Unknown letters case.");
    }
}
