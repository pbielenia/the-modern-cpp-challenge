#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

template<typename T, typename U> std::vector<T> extract_digits(U number)
{
    std::vector<T> digits;

    digits.push_back(number / 100);
    digits.push_back(number % 100 / 10);
    digits.push_back(number % 10);

    return digits;
}

template<typename T> void to_the_third_power(std::vector<T>& numbers)
{
    std::transform(numbers.begin(), numbers.end(), numbers.begin(),
                   [](T i) { return i * i * i; });
}

template<typename T> std::vector<T> generate_armstrong_numbers()
{
    std::vector<T> result;

    for (int i = 100; i < 999; ++i) {
        auto digits = extract_digits<T>(i);
        to_the_third_power(digits);
        auto digits_sum = std::accumulate(digits.begin(), digits.end(), 0);
        if (i == digits_sum)
            result.push_back(i);
    }

    return result;
}
