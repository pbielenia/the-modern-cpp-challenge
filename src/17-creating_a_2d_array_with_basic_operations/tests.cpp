#include <gmock/gmock.h>
#include "Array2D.hpp"

using namespace testing;

TEST(Array2D, ConstructsFromTemplateWithTypeRowsAndColumnsNumber) {
    Array2D<int, 2, 3>{};
}
