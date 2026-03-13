#pragma once

#include <cassert>
#include <cstddef>
#include <vector>

namespace solution {

template <typename T>
class CircularBuffer {
 public:
  CircularBuffer() = delete;
  explicit CircularBuffer(size_t capacity);

  bool IsFull() const noexcept;
  size_t Size() const noexcept;
  size_t Capacity() const noexcept;

  void Push(T&& item);
  void PopFront();

  const T& Front() const;
  const T& Back() const;

 private:
  class CircularMarker {
   public:
    explicit CircularMarker(std::size_t range, std::size_t index = 0)
        : range_(range),
          index_(index) {}

    void Advance() { index_ = (index_ + 1) % range_; }

    CircularMarker Previous() const {
      auto copy = *this;
      copy.Recede();
      return copy;
    }
    size_t Index() const { return index_; }

   private:
    std::size_t range_;
    std::size_t index_;
  };

  std::vector<T> data_;
  std::size_t size_;
  CircularMarker read_position_;
  CircularMarker write_position_;
};

template <typename T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : data_(capacity),
      size_(0),
      read_position_(capacity, 0),
      write_position_(capacity, 0) {
  assert(capacity > 0);
}

template <typename T>
bool CircularBuffer<T>::IsFull() const noexcept {
  return Size() == Capacity();
}

template <typename T>
size_t CircularBuffer<T>::Size() const noexcept {
  return size_;
}

template <typename T>
size_t CircularBuffer<T>::Capacity() const noexcept {
  return data_.size();
}

template <typename T>
void CircularBuffer<T>::Push(T&& item) {
  if (IsFull()) {
    read_position_.Advance();
  }

  data_[write_position_.Index()] = std::move(item);
  write_position_.Advance();
  size_ = std::min(size_ + 1, Capacity());

}

template <typename T>
void CircularBuffer<T>::PopFront() {
  if (Size() == 0) {
    return;
  }

  data_[read_position_.Index()] = T();
  read_position_.Advance();
  size_--;
}

template <typename T>
const T& CircularBuffer<T>::Front() const {
  return data_.at(read_position_.Index());
}

}  // namespace solution
