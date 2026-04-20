#pragma once

#include <algorithm>
#include <cstddef>
#include <execution>
#include <iterator>
#include <thread>
#include <vector>

namespace solution {

template <typename T, typename Callable>
std::vector<T> ProcessSerial(std::vector<T> dataset,
                             Callable processing_callable) {
  std::for_each(std::execution::seq, dataset.begin(), dataset.end(),
                processing_callable);
  return dataset;
}

template <typename T, typename Callable>
std::vector<T> ProcessParallelStl(std::vector<T> dataset,
                                  Callable processing_callable) {
  std::for_each(std::execution::par, dataset.begin(), dataset.end(),
                processing_callable);
  return dataset;
}

namespace details {

static constexpr size_t kMaxBatchesCount = 16;

template <typename T>
using MutableBatchRanges =
    std::array<std::pair<typename std::vector<T>::iterator,
                         typename std::vector<T>::iterator>,
               kMaxBatchesCount>;

template <typename T>
std::pair<MutableBatchRanges<T>, std::size_t> MakeMutableBatchRanges(
    std::vector<T>& dataset, std::size_t batch_count) {
  MutableBatchRanges<T> batch_ranges;

  if (dataset.empty() || batch_count == 0 || batch_count > dataset.size() ||
      batch_count > kMaxBatchesCount) {
    return {batch_ranges, 0};
  }

  if (dataset.size() == 1) {
    batch_ranges[0] = {dataset.begin(), dataset.end()};
    return {batch_ranges, 1};
  }

  const auto batch_size = dataset.size() / batch_count;

  for (size_t index = 0; index < batch_count; ++index) {
    const auto start_index = index * batch_size;
    const auto end_index = start_index + batch_size;
    auto start_item = std::next(dataset.begin(), start_index);
    auto end_item = std::next(dataset.begin(), end_index);
    batch_ranges[index] = {start_item, end_item};
  }

  batch_ranges[batch_count - 1].second = dataset.end();
  return {batch_ranges, batch_count};
}

}  // namespace details

template <typename T, typename Callable>
std::vector<T> ProcessParallelCustom(std::vector<T> dataset,
                                     Callable processing_callable) {
  const auto available_threads_count = std::thread::hardware_concurrency();
  if (available_threads_count == 0) {
    std::ranges::for_each(dataset, processing_callable);
    return dataset;
  }

  auto [batch_ranges, batch_count] =
      details::MakeMutableBatchRanges(dataset, available_threads_count);
  std::vector<std::thread> threads;

  for (size_t index = 0; index < batch_count; ++index) {
    auto& [batch_start, batch_end] = batch_ranges[index];
    threads.emplace_back([batch_start, batch_end, processing_callable]() {
      std::for_each(batch_start, batch_end, processing_callable);
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  return dataset;
}

}  // namespace solution
