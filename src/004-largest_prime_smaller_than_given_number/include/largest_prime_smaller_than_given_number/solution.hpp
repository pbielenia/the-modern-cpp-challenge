#pragma once

#include <cmath>
#include <vector>

std::vector<unsigned int> sieve_of_eratosthenes(unsigned int upper_bound)
{
    std::vector<bool> truth_array(upper_bound, true);

    for (int i = 2; i < std::sqrt(upper_bound); ++i) {
        if (truth_array[i] == true) {
            for (unsigned j = i ^ 2; j < upper_bound; j += i) {
                truth_array[j] = false;
            }
        }
    }

    std::vector<unsigned int> prime_numbers;
    for (unsigned i = 0; i < truth_array.size(); ++i) {
        if (truth_array[i] == true) {
            prime_numbers.push_back(i);
        }
    }

    return prime_numbers;
}

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

unsigned int find_closest_prime(unsigned int a)
{
    for (unsigned int i = a; i > 0; --i) {
        auto result = is_prime(i);
        if (result == true)
            return i;
    }
    return 0;
}
