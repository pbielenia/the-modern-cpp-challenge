#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

TEST(DeserializeFixture, NoNameYet) {
  solution::Deserialize(std::string{RESOURCE_DIR}.append("/movies-list.xml"));
}

}  // namespace