#include <memory>

#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

class CircularBufferFixture : public testing::Test {
 public:
  size_t buffer_capacity_ = 0;
  std::shared_ptr<solution::CircularBuffer<int>> buffer_;

  struct State {
    bool is_full = false;
    size_t size = 0;
    std::optional<int> front;
  };

 protected:
  void TearDown() override {
    buffer_capacity_ = 0;
    buffer_.reset();
  }

  void VerifyState(const State& state) const {
    ASSERT_EQ(buffer_->IsFull(), state.is_full) << state;
    ASSERT_EQ(buffer_->Capacity(), buffer_capacity_) << state;
    ASSERT_EQ(buffer_->Size(), state.size) << state;

    if (state.front.has_value()) {
      ASSERT_EQ(buffer_->Front(), state.front) << state;
    }
  }
};

std::ostream& operator<<(std::ostream& stream,
                         const std::optional<int>& optional) {
  stream << (optional.has_value() ? std::to_string(optional.value()) : "n/a");
  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const CircularBufferFixture::State& state) {
  stream << std::boolalpha << "{ is_full: " << state.is_full
         << ", size: " << state.size << ", front: " << state.front << " }";
  return stream;
};

TEST_F(CircularBufferFixture, Mixed) {
  buffer_capacity_ = 3;
  buffer_ = std::make_shared<solution::CircularBuffer<int>>(buffer_capacity_);

  // [ __ __ ]
  //    ^
  VerifyState({.is_full = false, .size = 0});
  buffer_->Push(10);
  // [ 10 __ __ ]
  //    ^
  VerifyState({.is_full = false, .size = 1, .front = 10});

  buffer_->Push(20);
  // [ 10 20 __ ]
  //    ^--^
  VerifyState({.is_full = false, .size = 2, .front = 10});

  buffer_->Push(30);
  // [ 10 20 30 ]
  //    ^-----^
  VerifyState({.is_full = true, .size = 3, .front = 10});

  buffer_->Push(40);
  // [ 40 20 30 ]
  // ---^  ^-----
  VerifyState({.is_full = true, .size = 3, .front = 20});

  buffer_->PopFront();
  // [ 40 __ 30 ]
  // ---^     ^--
  VerifyState({.is_full = false, .size = 2, .front = 30});

  buffer_->Push(50);
  // [ 40 50 30 ]
  // ------^  ^--
  VerifyState({.is_full = true, .size = 3, .front = 30});

  buffer_->PopFront();
  // [ 40 50 __ ]
  //    ^--^
  VerifyState({.is_full = false, .size = 2, .front = 40});

  buffer_->PopFront();
  // [ __ 50 __ ]
  //       ^
  VerifyState({.is_full = false, .size = 1, .front = 50});

  buffer_->PopFront();
  // [ __ __ __ ]
  //       ^
  VerifyState({.is_full = false, .size = 0});

  buffer_->PopFront();
  // [ __ __ __ ]
  //       ^
  VerifyState({.is_full = false, .size = 0});

  buffer_->Push(60);
  // [ __ 60 __ ]
  //       ^
  VerifyState({.is_full = false, .size = 1, .front = 60});
}

}  // namespace