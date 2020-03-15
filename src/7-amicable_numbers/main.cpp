#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <map>
#include <vector>


unsigned long sum_proper_divisors(unsigned int const n)
{
    unsigned long sum = 0;

    for (unsigned i = 1; i < n; ++i)
        if (n % i == 0) sum += i;
    return sum;
}

void print_amicables(unsigned int const limit)
{
    for (unsigned int i = 2; i <= limit; ++i) {
        auto divisors_sum_1 = sum_proper_divisors(i);
        auto divisors_sum_2 = sum_proper_divisors(divisors_sum_1);

        if ((i == divisors_sum_2) && (divisors_sum_1 > divisors_sum_2))
            std::cout << divisors_sum_1 << " : " << divisors_sum_2 << "\n" ;
    }
    std::cout << std::flush;
}

int main()
{
    print_amicables(1000000);
}
