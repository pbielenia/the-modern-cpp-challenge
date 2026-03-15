#include <algorithm>
#include <chrono>
#include <iomanip>
#include <numeric>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

using solution::FindMostFrequentItemVariantA;
using solution::FindMostFrequentItemVariantB;
using solution::MostFrequentItems;
using namespace testing;

struct MostFrequentTestData {
  std::vector<int> input;
  unsigned expected_count;
  std::vector<int> expected_values;
};

class MostFrequentItemsFixture
    : public testing::TestWithParam<MostFrequentTestData> {};

TEST_P(MostFrequentItemsFixture, VariantA) {
  const auto& data = GetParam();
  const MostFrequentItems<int> result =
      FindMostFrequentItemVariantA(data.input);
  EXPECT_THAT(result.count, Eq(data.expected_count));
  EXPECT_THAT(result.values, UnorderedElementsAreArray(data.expected_values));
}

TEST_P(MostFrequentItemsFixture, VariantB) {
  const auto& data = GetParam();
  const MostFrequentItems<int> result =
      FindMostFrequentItemVariantB(data.input);
  EXPECT_THAT(result.count, Eq(data.expected_count));
  EXPECT_THAT(result.values, UnorderedElementsAreArray(data.expected_values));
}

INSTANTIATE_TEST_SUITE_P(MostFrequentCommon,
                         MostFrequentItemsFixture,
                         testing::Values(
                             MostFrequentTestData{
                                 .input = {},
                                 .expected_count = 0,
                                 .expected_values = {},
                             },
                             MostFrequentTestData{
                                 .input = {1},
                                 .expected_count = 1,
                                 .expected_values = {1},
                             },
                             MostFrequentTestData{
                                 .input = {1, 2, 3},
                                 .expected_count = 1,
                                 .expected_values = {1, 2, 3},
                             },
                             MostFrequentTestData{
                                 .input = {1, 1, 2, 3},
                                 .expected_count = 2,
                                 .expected_values = {1},
                             },
                             MostFrequentTestData{
                                 .input = {5, 1, 5, 2, 2, 8},
                                 .expected_count = 2,
                                 .expected_values = {2, 5},
                             },
                             MostFrequentTestData{
                                 .input = {4, 4, 4, 4},
                                 .expected_count = 4,
                                 .expected_values = {4},
                             }));

TEST(MostFrequentItems, DISABLED_StringElementTypeSupportsValueList) {
  const std::vector<std::string> dataset = {"apple", "banana", "apple",
                                            "orange", "banana"};

  const MostFrequentItems<std::string> actual_a =
      FindMostFrequentItemVariantA(dataset);
  EXPECT_THAT(actual_a.count, Eq(2));
  EXPECT_THAT(actual_a.values, ElementsAre("apple", "banana"));

  const MostFrequentItems<std::string> actual_b =
      FindMostFrequentItemVariantB(dataset);
  EXPECT_THAT(actual_b.count, Eq(2));
  EXPECT_THAT(actual_b.values, ElementsAre("apple", "banana"));
}

struct PerfParam {
  std::string name;
  std::function<MostFrequentItems<int>(const std::vector<int>&)> function;
  int dataset_size;
  int distinct;
  int repeats;
  int warmup_runs;
};

class MostFrequentPerformanceFixture
    : public testing::TestWithParam<PerfParam> {};

TEST_P(MostFrequentPerformanceFixture, DISABLED_Measurements) {
  const auto& params = GetParam();

  std::vector<int> dataset;
  dataset.reserve(params.dataset_size);
  for (int i = 0; i < params.dataset_size; ++i) {
    dataset.push_back(i % params.distinct);
  }

  // Warmup run(s) to reduce cold-start noise
  for (int i = 0; i < params.warmup_runs; ++i) {
    volatile auto result = params.function(dataset);
    (void)result;
  }

  std::vector<long long> run_times;
  run_times.reserve(params.repeats);
  volatile unsigned count = 0;

  for (int i = 0; i < params.repeats; ++i) {
    const auto start = std::chrono::steady_clock::now();
    const auto result = params.function(dataset);
    const auto end = std::chrono::steady_clock::now();
    count += result.count;
    run_times.push_back(
        std::chrono::duration_cast<std::chrono::microseconds>(end - start)
            .count());
  }

  const auto min_time = *std::ranges::min_element(run_times);
  const auto max_time = *std::ranges::max_element(run_times);
  const auto avg_time =
      std::accumulate(run_times.begin(), run_times.end(), 0LL) /
      static_cast<long long>(run_times.size());

  std::cout << std::left << std::setw(24) << params.name
            << " size=" << std::setw(7) << params.dataset_size
            << " distinct=" << std::setw(6) << params.distinct
            << " repeats=" << std::setw(3) << params.repeats
            << " min_us=" << std::setw(6) << min_time
            << " max_us=" << std::setw(6) << max_time
            << " avg_us=" << std::setw(6) << avg_time << "\n";

  EXPECT_GT(count, 0);
  EXPECT_EQ(run_times.size(), static_cast<size_t>(params.repeats));
}

TEST(MostFrequentPerformance, Simple) {
  const int dataset_size = 10'000;
  const int distinct = 1'000;

  std::vector<int> dataset;
  dataset.reserve(dataset_size);
  for (int i = 0; i < dataset_size; ++i) {
    dataset.push_back(i % distinct);
  }

  volatile auto result = FindMostFrequentItemVariantB<int>(dataset);
  (void)result.count;
}

INSTANTIATE_TEST_SUITE_P(MostFrequentPerformance,
                         MostFrequentPerformanceFixture,
                         testing::Values(
                             PerfParam{
                                 .name = "VariantA N=10k D=1k",
                                 .function = FindMostFrequentItemVariantA<int>,
                                 .dataset_size = 100'000,
                                 .distinct = 1'000,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             },
                             PerfParam{
                                 .name = "VariantA N=1k D=1k",
                                 .function = FindMostFrequentItemVariantA<int>,
                                 .dataset_size = 10'000,
                                 .distinct = 1'000,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             },
                             PerfParam{
                                 .name = "VariantA N=10k D=100",
                                 .function = FindMostFrequentItemVariantA<int>,
                                 .dataset_size = 100'000,
                                 .distinct = 100,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             },
                             PerfParam{
                                 .name = "VariantB N=10k D=1k",
                                 .function = FindMostFrequentItemVariantB<int>,
                                 .dataset_size = 100'000,
                                 .distinct = 1'000,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             },
                             PerfParam{
                                 .name = "VariantB N=1k D=1k",
                                 .function = FindMostFrequentItemVariantB<int>,
                                 .dataset_size = 10'000,
                                 .distinct = 1'000,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             },
                             PerfParam{
                                 .name = "VariantB N=10k D=100",
                                 .function = FindMostFrequentItemVariantB<int>,
                                 .dataset_size = 100'000,
                                 .distinct = 100,
                                 .repeats = 50,
                                 .warmup_runs = 1,
                             }));

}  // namespace
