#pragma once

unsigned int gcd_recursive(unsigned int a, unsigned int b)
{
    auto c = a % b;

    if (c == 0)
        return b;
    else
        return gcd_recursive(b, c);
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
