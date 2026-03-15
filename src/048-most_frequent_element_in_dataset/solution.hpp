#pragma once

#include <algorithm>
#include <iterator>
#include <optional>
#include <unordered_map>
#include <vector>

namespace solution {

namespace details {

template <typename T>
std::vector<T> GetUniqueItems(std::vector<T> dataset) {
  std::ranges::sort(dataset);
  const auto [unique_first, unique_last] = std::ranges::unique(dataset);
  dataset.erase(unique_first, unique_last);
  return dataset;
}

template <typename T>
std::unordered_map<T, unsigned> CountItems(const std::vector<T>& dataset) {
  std::unordered_map<T, unsigned> item_counts;
  for (const auto& item : dataset) {
    item_counts[item]++;
  }
  return item_counts;
}

template <typename T>
std::optional<unsigned> FindMaxCount(
    const std::unordered_map<T, unsigned>& item_counts) {
  if (item_counts.empty()) {
    return std::nullopt;
  }
  const auto max_count_iterator = std::ranges::max_element(
      item_counts,
      [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
  return max_count_iterator->second;
}

template <typename T>
std::vector<T> FindItemsWithCount(
    const std::unordered_map<T, unsigned>& item_counts,
    unsigned searched_count) {
  std::vector<T> found_items;

  auto search_beginning = item_counts.begin();
  const auto search_end = item_counts.end();
  while (true) {
    const auto search_result =
        std::find_if(search_beginning, search_end,
                     [&searched_count](const auto& item_count) {
                       const auto& count = item_count.second;
                       return count == searched_count;
                     });
    if (search_result == search_end) {
      return found_items;
    }

    const auto& item = search_result->first;
    found_items.push_back(item);
    search_beginning = std::next(search_result);
  }
}

}  // namespace details

template <typename T>
struct MostFrequentItems {
  unsigned count = 0;
  std::vector<T> values;
};

template <typename T>
MostFrequentItems<T> FindMostFrequentItemVariantA(
    const std::vector<T>& dataset) {
  const auto item_counts = details::CountItems(dataset);
  const auto max_count = details::FindMaxCount(item_counts);
  if (!max_count.has_value()) {
    return {};
  }

  return MostFrequentItems<T>{
      .count = max_count.value(),
      .values = details::FindItemsWithCount(item_counts, max_count.value()),
  };
}

template <typename T>
MostFrequentItems<T> FindMostFrequentItemVariantB(
    const std::vector<T>& dataset) {
  const auto item_counts = details::CountItems(dataset);
  const auto max_count = details::FindMaxCount(item_counts);
  if (!max_count.has_value()) {
    return {};
  }

  MostFrequentItems<T> most_frequent_items{
      .count = max_count.value(),
  };

  for (const auto& [item, count] : item_counts) {
    if (count == max_count.value()) {
      most_frequent_items.values.push_back(item);
    }
  }

  return most_frequent_items;
}

}  // namespace solution