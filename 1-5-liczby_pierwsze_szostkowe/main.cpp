#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(unsigned int n)
{
    if (n <= 3)
        return n > 1;
    else if ((n % 2 == 0) || (n % 3 == 0))
        return false;
    else {
        for (unsigned int i = 5; i * i <= n; i += 6 ) {
            if ((n % i == 0) || (n % (i + 2) == 0))
                return false;
        }
    }
    return true;
}

int main()
{
    constexpr unsigned int input = 100;

    for (int i = 0; i < (input - 6); ++i) {
        if (is_prime(i) && is_prime(i + 6)) {
            std::cout << i << ", " << i + 6 << std::endl;
        }
    }

}
