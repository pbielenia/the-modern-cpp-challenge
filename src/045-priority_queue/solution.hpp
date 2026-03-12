#pragma once

#include <functional>
#include <set>

namespace solution {

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
 public:
  explicit PriorityQueue(const Compare& compare = Compare{});

  void Push(const T& value);
  void Push(T&& value);
  void Pop();
  const T& Top() const;

  size_t Size() const;
  bool IsEmpty() const;

 private:
  std::set<T, Compare> data_;
};

template <typename T, typename Compare>
PriorityQueue<T, Compare>::PriorityQueue(const Compare& compare)
    : data_(compare) {}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::Push(const T& value) {
  data_.insert(value);
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::Push(T&& value) {
  data_.insert(std::move(value));
}

template <typename T, typename Compare>
void PriorityQueue<T, Compare>::Pop() {
  if (IsEmpty()) {
    return;
  }

  data_.erase(data_.begin());
}

template <typename T, typename Compare>
const T& PriorityQueue<T, Compare>::Top() const {
  return *(data_.begin());
}

template <typename T, typename Compare>
size_t PriorityQueue<T, Compare>::Size() const {
  return data_.size();
}

template <typename T, typename Compare>
bool PriorityQueue<T, Compare>::IsEmpty() const {
  return data_.empty();
}

}  // namespace solution