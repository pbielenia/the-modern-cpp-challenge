#include <iostream>
#include <numeric>
#include <cstdlib>
#include <utility>

unsigned int lcm_iterative(unsigned int a, unsigned int b)
{
    auto c = a * b;
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
    }

    return c / a;
}

unsigned int lcm_iterative(const std::pair<unsigned int, unsigned int>& numbers)
{
    return lcm_iterative(numbers.first, numbers.second);
}

unsigned int lcm_recursive(unsigned int a, unsigned int b)
{
    auto c = a * b;

    return c / lcm_recursive(b, a % b);
}

unsigned int lcm_recursive(const std::pair<unsigned int, unsigned int>& numbers)
{
    return lcm_recursive(numbers.first, numbers.second);
}

unsigned int lcd_using_gcd(std::pair<unsigned int, unsigned int>& numbers)
{
    return (numbers.first * numbers.second)
        / std::gcd(numbers.first, numbers.second);
}

int main()
{
    std::pair<unsigned int, unsigned int> numbers(48, 14);

    std::cout << "STL : " << std::lcm(numbers.first, numbers.second) << std::endl;
    std::cout << "Euclides iterative : " << lcm_iterative(numbers) << std::endl;
    std::cout << "Using gcd : " << lcd_using_gcd(numbers) << std::endl;
    // std::cout << "Euclides recursive : " << lcm_recursive(numbers) << std::endl;
}
