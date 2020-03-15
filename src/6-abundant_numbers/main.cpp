#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>


std::vector<unsigned int> get_proper_divisors(unsigned int const n)
{
    std::set<unsigned int> divisors;

    for (unsigned i = 1; i < n; ++i) {
        if (n % i == 0)
            divisors.insert(i);
    }

    return std::vector<unsigned int>(divisors.begin(), divisors.end());
}

long get_abundance(unsigned int const n, const unsigned long divisors_sum)
{
    return divisors_sum - n;
}

bool is_abundant_number(const unsigned int n, const unsigned long divisors_sum)
{
    return divisors_sum > n;
}

int main()
{
    unsigned int input;
    std::cout << "Specify limit: ";
    std::cin >> input;

    std::cout << std::setw(6) << "Number" << std::setw(10) << "Abundance" << std::endl;

    for (unsigned int i = 0; i <= input; ++i) {
        auto divisors = get_proper_divisors(i);
        auto divisors_sum = std::accumulate(divisors.begin(), divisors.end(), 0);

        if (is_abundant_number(i, divisors_sum)) {
            std::cout << std::setw(6) << i << std::setw(10)
                << get_abundance(i, divisors_sum) << std::endl;
        }
    }
}
