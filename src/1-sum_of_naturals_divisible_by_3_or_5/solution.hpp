#pragma once

unsigned long long sum_of_naturals_divisible_by_3_or_5(unsigned value_limit)
{
    unsigned long long sum{0};

    for (unsigned int i = 3; i <= value_limit; ++i) {
        if ((i % 3) == 0 || (i % 5) == 0) {
            sum += i;
        }
    }
    return sum;
}
