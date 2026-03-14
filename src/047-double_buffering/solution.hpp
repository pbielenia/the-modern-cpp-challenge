#pragma once

#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>

namespace solution {

template <typename T, std::size_t Size>
class DoubleBuffer {
 public:
  static constexpr auto size = Size;
  using BufferType = std::array<T, Size>;

  // Reads from the currently active buffer at position.
  // Caller is responsible for validating position < size.
  const T& Read(std::size_t position) const;

  // Replace the full inactive buffer and publish it.
  // Readers will observe either the previous complete buffer or the new
  // complete buffer. This implementation assumes a single writer and zero or
  // many readers.
  void Write(const BufferType& buffer);

 private:
  std::array<BufferType, 2> buffers_{};
  std::atomic<std::uint8_t> read_index_ = 0;
};

template <typename T, std::size_t Size>
const T& DoubleBuffer<T, Size>::Read(std::size_t position) const {
  return buffers_[read_index_.load(std::memory_order_acquire)][position];
}

template <typename T, std::size_t Size>
void DoubleBuffer<T, Size>::Write(
    const typename DoubleBuffer<T, Size>::BufferType& buffer) {
  auto write_index = 1 - read_index_.load(std::memory_order_relaxed);
  buffers_[write_index] = buffer;
  read_index_.store(write_index, std::memory_order_release);
}

}  // namespace solution