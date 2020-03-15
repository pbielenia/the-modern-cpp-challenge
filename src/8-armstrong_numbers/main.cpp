#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

template<typename T>
void print_vector(const std::vector<T>& vect)
{
    for (const auto& elem : vect) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

template<typename T, typename U>
std::vector<T> extract_digits(U number)
{
    std::vector<T> digits;
    
    digits.push_back(number / 100);
    digits.push_back(number % 100 / 10);
    digits.push_back(number % 10);
    
    return digits;
}

template<typename T>
void to_the_third_power(std::vector<T>& numbers)
{
    std::transform(numbers.begin(), numbers.end(), numbers.begin(),
        [](T i) { return i*i*i; });
}

int main()
{
    for (int i = 100; i < 999; ++i) {
        auto digits = extract_digits<unsigned short>(i);
        to_the_third_power(digits);
        auto digits_sum = std::accumulate(digits.begin(), digits.end(), 0);
        if (i == digits_sum)
            std::cout << i << "\n";
    }
    std::cout << std::flush;
}
