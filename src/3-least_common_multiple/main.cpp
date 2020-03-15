#include <iostream>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <utility>

int lcm_iterative(int a, int b)
{
    auto _c = a * b;
    auto _a = a;
    auto _b = b;

    while (_b != 0) {
        auto t = _b;
        _b = _a % _b;
        _a = t;
    }

    return _c / _a;
}

int lcm_iterative(const std::pair<int, int>& numbers)
{
    return lcm_iterative(numbers.first, numbers.second);
}

int lcm_recursive(int const a, int const b)
{
    auto c = a * b;

    return c / lcm_recursive(b, a % b);
}

int lcm_recursive(const std::pair<int const, int const>& numbers)
{
    return lcm_recursive(numbers.first, numbers.second);
}

int lcd_using_gcd(int a, int b)
{
    return std::abs(a * b)
        / std::gcd(a, b);
}

int lcd_using_gcd(std::pair<int const, int const>& numbers)
{
    return lcd_using_gcd(numbers.first, numbers.second);
}

template<class InputIter>
int lcmr(InputIter first, InputIter last)
{
    return std::accumulate(first, last, 1, static_cast<int(*)(int, int)>(&lcm_iterative));
}

int main()
{
    std::pair<int const, int const> numbers(-48, 14);
    std::vector<int> vector_of_numbers;
    vector_of_numbers.push_back(48);
    vector_of_numbers.push_back(14);

    std::cout << "STL : " << std::lcm(numbers.first, numbers.second) << std::endl;
    std::cout << "Euclides iterative : " << lcm_iterative(numbers) << std::endl;
    std::cout << "Using gcd : " << lcd_using_gcd(numbers) << std::endl;
    // std::cout << "Euclides recursive : " << lcm_recursive(numbers) << std::endl;
    std::cout << "Multiple inputs : " << lcmr(vector_of_numbers.begin(), vector_of_numbers.end()) << std::endl;
}
