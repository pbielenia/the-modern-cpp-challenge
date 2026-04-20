#include <cstddef>
#include <iterator>
#include <mutex>
#include <random>
#include <set>
#include <thread>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

constexpr int kBatchRangeDataEnd = -1;

struct MakeMutableBatchRangesTestParams {
  std::vector<int> input_data;
  std::size_t batch_count;
  std::vector<std::pair<int, int>> expected_value_ranges;
};

std::ostream& operator<<(std::ostream& stream,
                         const std::pair<int, int>& pair) {
  stream << "{" << pair.first << ", " << pair.second << "}";
  return stream;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& vector) {
  stream << "[ ";

  bool is_first = true;
  for (const auto& item : vector) {
    if (is_first) {
      is_first = false;
      stream << item;
      continue;
    }

    stream << ", " << item;
  }

  stream << " ]";

  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const MakeMutableBatchRangesTestParams& params) {
  stream << "{ input_data: " << params.input_data
         << ", batch_count: " << params.batch_count
         << ", expected_value_ranges: " << params.expected_value_ranges << " }";
  return stream;
}

class MakeMutableBatchRangesTest
    : public testing::TestWithParam<MakeMutableBatchRangesTestParams> {
 protected:
  using MutableBatchRanges = solution::details::MutableBatchRanges<int>;
  using ValueRanges = std::vector<std::pair<int, int>>;

  static ValueRanges ToValueRanges(const std::vector<int>& dataset,
                                   const MutableBatchRanges& iterator_ranges,
                                   std::size_t ranges_count) {
    ValueRanges value_ranges;
    for (size_t i = 0; i < ranges_count; ++i) {
      const auto& iterator_range = iterator_ranges.at(i);
      value_ranges.emplace_back(ToValue(dataset, iterator_range.first),
                                ToValue(dataset, iterator_range.second));
    }
    return value_ranges;
  }

 private:
  static int ToValue(const std::vector<int>& data,
                     const std::vector<int>::iterator& range_item) {
    return (range_item == data.end()) ? kBatchRangeDataEnd : *range_item;
  }
};

TEST_P(MakeMutableBatchRangesTest, Main) {
  auto input_data = GetParam().input_data;
  const auto batch_count = GetParam().batch_count;

  const auto [actual_iterator_ranges, ranges_count] =
      solution::details::MakeMutableBatchRanges(input_data, batch_count);
  const auto actual_value_ranges =
      ToValueRanges(input_data, actual_iterator_ranges, ranges_count);
  EXPECT_THAT(actual_value_ranges,
              testing::ContainerEq(GetParam().expected_value_ranges));
}

INSTANTIATE_TEST_SUITE_P(Main,
                         MakeMutableBatchRangesTest,
                         testing::Values(
                             MakeMutableBatchRangesTestParams{
                                 .input_data = {0, 1, 2, 3, 4},
                                 .batch_count = 2,
                                 .expected_value_ranges =
                                     {
                                         {0, 2},
                                         {2, kBatchRangeDataEnd},
                                     },
                             },
                             MakeMutableBatchRangesTestParams{
                                 .input_data = {0, 1, 2, 3, 4},
                                 .batch_count = 3,
                                 .expected_value_ranges =
                                     {
                                         {0, 1},
                                         {1, 2},
                                         {2, kBatchRangeDataEnd},
                                     },
                             },
                             MakeMutableBatchRangesTestParams{
                                 .input_data = {0, 1, 2, 3, 4},
                                 .batch_count = 4,
                                 .expected_value_ranges =
                                     {
                                         {0, 1},
                                         {1, 2},
                                         {2, 3},
                                         {3, kBatchRangeDataEnd},
                                     },
                             },
                             MakeMutableBatchRangesTestParams{
                                 .input_data = {0, 1, 2, 3, 4},
                                 .batch_count = 5,
                                 .expected_value_ranges =
                                     {
                                         {0, 1},
                                         {1, 2},
                                         {2, 3},
                                         {3, 4},
                                         {4, kBatchRangeDataEnd},
                                     },
                             },
                             MakeMutableBatchRangesTestParams{
                                 .input_data = {0, 1, 2, 3, 4},
                                 .batch_count = 6,
                                 .expected_value_ranges = {},
                             }));

class ConcurrentTransformTest : public testing::Test {
 protected:
  using GenerateRandomVectorData = int;
  using GenerateRandomVectorContainer = std::vector<GenerateRandomVectorData>;
  GenerateRandomVectorContainer GenerateRandomVector() const {
    if (generated_random_count_ == 0) {
      return {};
    }

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(-generated_random_range_,
                                                 generated_random_range_);

    GenerateRandomVectorContainer dataset;
    dataset.reserve(generated_random_count_);
    std::ranges::generate_n(
        std::back_inserter(dataset), generated_random_count_,
        [&distribution, &generator]() { return distribution(generator); });

    return dataset;
  }

  static void VerifyResult(const std::vector<int>& input,
                           const std::vector<int>& result) {
    ASSERT_THAT(result, testing::SizeIs(input.size()));

    const auto expected = MakeExpectedDataset(input);
    EXPECT_THAT(result, testing::ContainerEq(expected));
  }

  static void ProcessingFunction(int& data) { data = (data * 7 + 11) % 10'000; }

 private:
  const unsigned short generated_random_range_ = 1'000;
  const unsigned generated_random_count_ = 10'000'000;

  std::set<std::thread::id> threads_ids_;
  std::mutex thread_ids_mutex_;

  static std::vector<int> MakeExpectedDataset(std::vector<int> dataset) {
    for (auto& item : dataset) {
      ProcessingFunction(item);
    }
    return dataset;
  }
};

TEST_F(ConcurrentTransformTest, ProcessSerial) {
  const auto dataset = GenerateRandomVector();
  const auto result = solution::ProcessSerial<int>(
      dataset, [](int& data) { ProcessingFunction(data); });
  VerifyResult(dataset, result);
}

TEST_F(ConcurrentTransformTest, ProcessParallelStl) {
  const auto dataset = GenerateRandomVector();
  const auto result = solution::ProcessParallelStl<int>(
      dataset, [](int& data) { ProcessingFunction(data); });
  VerifyResult(dataset, result);
}

TEST_F(ConcurrentTransformTest, ProcessParallelCustom) {
  const auto dataset = GenerateRandomVector();
  const auto result = solution::ProcessParallelCustom<int>(
      dataset, [this](int& data) { ProcessingFunction(data); });
  VerifyResult(dataset, result);
}

}  // namespace
