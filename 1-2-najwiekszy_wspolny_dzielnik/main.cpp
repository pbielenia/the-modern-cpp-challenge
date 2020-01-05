#include <iostream>
#include <numeric>

unsigned int gcd_recursive(unsigned int a, unsigned int b)
{
    auto c = a % b;

    if (c == 0) return b;
    else return gcd_recursive(b, c);
}

unsigned int gcd_recursive(const std::pair<unsigned int, unsigned int>& numbers)
{
    return gcd_recursive(numbers.first, numbers.second);
}

unsigned int gcd_iterative(unsigned int a, unsigned int b)
{
    unsigned int c{0};

    do {
        c = a % b;
        a = b;
        b = c;
    } while (c != 0);

    return a;
}

unsigned int gcd_iterative(const std::pair<unsigned int, unsigned int>& numbers)
{
    return gcd_iterative(numbers.first, numbers.second);
}

int main()
{
    std::pair<unsigned int, unsigned int> numbers(148, 176);

    std::cout << "recursive Euclides : " << gcd_recursive(numbers) << '\n';
    std::cout << "iterative Euclides : " << gcd_iterative(numbers) << '\n';
    std::cout << "STL : " << std::gcd(numbers.first, numbers.second) << '\n';
    std::cout << std::flush;
}
