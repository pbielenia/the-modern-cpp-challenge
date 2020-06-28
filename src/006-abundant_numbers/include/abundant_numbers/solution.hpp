#pragma once

#include <numeric>
#include <set>
#include <vector>

using abundants_collection = std::vector<std::pair<unsigned, unsigned>>;

std::vector<unsigned int> get_proper_divisors(unsigned int const n)
{
    std::set<unsigned int> divisors;

    for (unsigned i = 2; i < n; ++i) {
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

abundants_collection calculate_abundants(unsigned limit)
{
    abundants_collection result;

    for (unsigned int i = 0; i <= limit; ++i) {
        auto divisors = get_proper_divisors(i);
        auto divisors_sum = std::accumulate(divisors.begin(), divisors.end(), 0);

        if (is_abundant_number(i, divisors_sum)) {
            auto abundance = get_abundance(i, divisors_sum);
            result.push_back(std::make_pair(i, abundance));
        }
    }

    return result;
}
