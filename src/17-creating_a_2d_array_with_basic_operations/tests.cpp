#include <gmock/gmock.h>
#include "Array2D.hpp"

using namespace testing;

TEST(Array2D, ConstructsFromTemplateWithTypeRowsAndColumnsNumber) {
    Array2D<int, 2, 3>{};
}

TEST(Array2D, ConstructsWithGivenElements) {
    Array2D<char, 2, 3>{'a', 'b', 'c', 'd', 'e', 'f'};
}

TEST(Array2D, ThrowsWhileConstructingWithTooMuchElements) {
    ASSERT_THROW((Array2D<char, 2, 3>{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}),
                 PassedElementsExceedArraySizeException);
}

TEST(Array2D, ThrowsWhileConstructingWithTooLittleElements) {
    ASSERT_THROW((Array2D<char, 2, 3>{'a', 'b', 'c', 'd', 'e'}),
                 PassedElementsDoNotReachArraySizeException);
}
