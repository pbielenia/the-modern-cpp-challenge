#include "gtest/gtest.h"

#include "solution.hpp"

namespace {

TEST(DoubleBufferTest, DefaultValuesAreZeroInitialized) {
  solution::DoubleBuffer<int, 4> buffer;

  EXPECT_EQ(buffer.Read(0), 0);
  EXPECT_EQ(buffer.Read(1), 0);
  EXPECT_EQ(buffer.Read(2), 0);
  EXPECT_EQ(buffer.Read(3), 0);
}

TEST(DoubleBufferTest, WriteThenReadUpdatesValues) {
  solution::DoubleBuffer<int, 3> buffer;
  solution::DoubleBuffer<int, 3>::BufferType frame{};
  frame[0] = 10;
  frame[1] = 20;
  frame[2] = 30;

  buffer.Write(frame);
  EXPECT_EQ(buffer.Read(0), 10);
  EXPECT_EQ(buffer.Read(1), 20);
  EXPECT_EQ(buffer.Read(2), 30);

  frame[1] = 99;
  buffer.Write(frame);
  EXPECT_EQ(buffer.Read(1), 99);
}

TEST(DoubleBufferTest, WriteWorksForAnyType) {
  solution::DoubleBuffer<std::string, 2> buffer;
  solution::DoubleBuffer<std::string, 2>::BufferType frame;
  frame[0] = "hello";
  frame[1] = "world";

  buffer.Write(frame);

  EXPECT_EQ(buffer.Read(0), "hello");
  EXPECT_EQ(buffer.Read(1), "world");
}

TEST(DoubleBufferTest, ReadAfterMultipleWritesReturnsLatestBuffer) {
  solution::DoubleBuffer<int, 2> buffer;
  solution::DoubleBuffer<int, 2>::BufferType first{};
  first[0] = 1;
  first[1] = 2;
  buffer.Write(first);

  solution::DoubleBuffer<int, 2>::BufferType second{};
  second[0] = 11;
  second[1] = 12;
  buffer.Write(second);

  EXPECT_EQ(buffer.Read(0), 11);
  EXPECT_EQ(buffer.Read(1), 12);
}

}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
