#include <iostream>
#include <numeric>
#include <cstdlib>
#include <utility>

int lcm_iterative(int const a, int const b)
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

int lcm_iterative(const std::pair<int const, int const>& numbers)
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

int lcd_using_gcd(std::pair<int const, int const>& numbers)
{
    return std::abs(numbers.first * numbers.second)
        / std::gcd(numbers.first, numbers.second);
}



int main()
{
    std::pair<int const, int const> numbers(-48, 14);

    std::cout << "STL : " << std::lcm(numbers.first, numbers.second) << std::endl;
    std::cout << "Euclides iterative : " << lcm_iterative(numbers) << std::endl;
    std::cout << "Using gcd : " << lcd_using_gcd(numbers) << std::endl;
    // std::cout << "Euclides recursive : " << lcm_recursive(numbers) << std::endl;
}
