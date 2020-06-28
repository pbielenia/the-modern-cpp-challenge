#include "largest_prime_smaller_than_given_number/solution.hpp"
#include <gmock/gmock.h>
#include <numeric>

using namespace testing;

TEST(FindClosestPrime, ReturnsCorrectFrom10) {
  ASSERT_THAT(find_closest_prime(10), 7);
}

TEST(FindClosestPrime, ReturnsCorrectFrom100) {
  ASSERT_THAT(find_closest_prime(100), 97);
}

TEST(FindClosestPrime, ReturnsCorrectFrom600) {
  ASSERT_THAT(find_closest_prime(600), 599);
}

TEST(SieveOfEratosthenes, ReturnsCorrectFrom10) {
  ASSERT_THAT(sieve_of_eratosthenes(10).back(), 7);
}

TEST(SieveOfEratosthenes, ReturnsCorrectFrom100) {
  ASSERT_THAT(sieve_of_eratosthenes(100).back(), 97);
}

TEST(SieveOfEratosthenes, ReturnsCorrectFrom600) {
  ASSERT_THAT(sieve_of_eratosthenes(600).back(), 599);
}
