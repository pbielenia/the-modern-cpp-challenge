#include <iostream>

int main()
{
    unsigned int upper_limit{0};
    unsigned long long sum{0};
    
    std::cout << "Give an upper limit: ";
    std::cin >> upper_limit;

    for (unsigned int i = 3; i <= upper_limit; ++i) {
        if ((i % 3) == 0 || (i % 5) == 0) {
            sum += i;
        }
    }
    std::cout << "The sum is equal to " << sum << std::endl;

}
