#pragma once

#include <vector>

// create a function returning vector of pairs

using vector_of_pairs = std::vector<std::pair<unsigned, unsigned>>;

bool is_prime(unsigned int n)
{
    if (n <= 3)
        return n > 1;
    else if ((n % 2 == 0) || (n % 3 == 0))
        return false;
    else {
        for (unsigned int i = 5; i * i <= n; i += 6) {
            if ((n % i == 0) || (n % (i + 2) == 0))
                return false;
        }
    }
    return true;
}

vector_of_pairs get_sexy_pairs(unsigned const limit)
{
    vector_of_pairs result;

    for (unsigned i = 0; i < (limit - 6); ++i) {
        if (is_prime(i) && is_prime(i + 6)) {
            result.push_back(std::make_pair(i, i + 6));
        }
    }

    return result;
}
