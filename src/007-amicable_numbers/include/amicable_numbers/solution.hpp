#pragma once

#include <vector>

using amicables_collection = std::vector<std::pair<unsigned long, unsigned long>>;

unsigned long sum_proper_divisors(unsigned int const n)
{
    unsigned long sum = 0;

    for (unsigned i = 1; i < n; ++i)
        if (n % i == 0)
            sum += i;
    return sum;
}

amicables_collection calculate_amicables(unsigned long limit)
{
    amicables_collection result;

    for (unsigned int i = 2; i <= limit; ++i) {
        auto divisors_sum_1 = sum_proper_divisors(i);
        auto divisors_sum_2 = sum_proper_divisors(divisors_sum_1);

        if ((i == divisors_sum_2) && (divisors_sum_1 > divisors_sum_2)) {
            result.push_back(std::make_pair(divisors_sum_2, divisors_sum_1));
        }
    }

    return result;
}
