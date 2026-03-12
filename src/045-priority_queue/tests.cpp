#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

TEST(PriorityQueueTest, DefaultCompareInt) {
  solution::PriorityQueue<int> queue;

  ASSERT_TRUE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 0);
  // Make sure it doesn't crash.
  queue.Pop();

  queue.Push(2);
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 1);
  ASSERT_EQ(queue.Top(), 2);

  queue.Push(3);
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 2);
  ASSERT_EQ(queue.Top(), 2);

  queue.Push(1);
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 3);
  ASSERT_EQ(queue.Top(), 1);

  queue.Pop();
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 2);
  ASSERT_EQ(queue.Top(), 2);

  queue.Pop();
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 1);
  ASSERT_EQ(queue.Top(), 3);

  queue.Pop();
  ASSERT_TRUE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 0);
}

struct CustomType {
  unsigned data;
};

bool operator==(const CustomType& lhs, const CustomType& rhs) {
  return lhs.data == rhs.data;
}

TEST(PriorityQueueTest, CustomCompareCustomType) {
  auto custom_compare = [](const CustomType& lhs, const CustomType& rhs) {
    return lhs.data > rhs.data;
  };

  solution::PriorityQueue<CustomType, decltype(custom_compare)> queue;

  ASSERT_TRUE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 0);
  // Make sure it doesn't crash.
  queue.Pop();

  queue.Push(CustomType{.data = 5});
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 1);
  ASSERT_EQ(queue.Top(), CustomType{.data = 5});

  queue.Push(CustomType{.data = 2});
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 2);
  ASSERT_EQ(queue.Top(), CustomType{.data = 5});

  queue.Push(CustomType{.data = 8});
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 3);
  ASSERT_EQ(queue.Top(), CustomType{.data = 8});

  queue.Pop();
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 2);
  ASSERT_EQ(queue.Top(), CustomType{.data = 5});

  queue.Pop();
  ASSERT_FALSE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 1);
  ASSERT_EQ(queue.Top(), CustomType{.data = 2});

  queue.Pop();
  ASSERT_TRUE(queue.IsEmpty());
  ASSERT_EQ(queue.Size(), 0);
}

}  // namespace