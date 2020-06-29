#pragma once

#include <string>
#include <vector>

class BinToStrConverter {
public:
    enum LettersCase { Lowercase, Uppercase };

    static std::string convert(const std::vector<unsigned char>& data,
                               LettersCase letters_case = Lowercase);

private:
    //
};
