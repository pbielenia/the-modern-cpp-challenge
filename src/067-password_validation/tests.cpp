#include <algorithm>
#include <cctype>
#include <iomanip>
#include <ostream>
#include <string_view>

#include "gtest/gtest.h"

#include "solution.hpp"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

namespace {

using namespace testing;

using Rule = solution::PasswordStrengthCalculator::Rule;
using Score = unsigned;

struct PasswordStrengthCalculatorTestData {
  std::vector<Rule> rules;
  std::map<std::string_view, Score> expected_scores;
};

std::ostream& operator<<(std::ostream& stream,
                         const std::map<std::string_view, Score>& data) {
  stream << "[ ";

  bool is_first = true;
  for (const auto& [password, score] : data) {
    if (is_first) {
      stream << "{" << std::quoted(password) << ", " << score << "}";
      is_first = false;
      continue;
    }
    stream << ", {" << std::quoted(password) << ", " << score << "}";
  }

  stream << " ]";

  return stream;
}

std::ostream& operator<<(std::ostream& stream,
                         const PasswordStrengthCalculatorTestData& data) {
  stream << "{ rules count: " << data.rules.size()
         << ", expected_scores: " << data.expected_scores << " }";
  return stream;
}

class PasswordStrengthCalculatorFixture
    : public TestWithParam<PasswordStrengthCalculatorTestData> {
 public:
  static void VerifyScores(
      const solution::PasswordStrengthCalculator& calculator,
      const std::map<std::string_view, unsigned>& expected_scores) {
    for (const auto& [password, expected_score] : expected_scores) {
      EXPECT_EQ(calculator.CalculatePasswordStrength(password), expected_score);
    }
  }
};

class SameWeightFixture : public PasswordStrengthCalculatorFixture {};

TEST_P(SameWeightFixture, RulesAddedInConstructor) {
  solution::PasswordStrengthCalculator calculator(GetParam().rules);
  VerifyScores(calculator, GetParam().expected_scores);
}

TEST_P(SameWeightFixture, AddRule) {
  solution::PasswordStrengthCalculator calculator;
  for (const auto& rule : GetParam().rules) {
    calculator.AddRule(rule);
  }
  VerifyScores(calculator, GetParam().expected_scores);
}

TEST_P(SameWeightFixture, AddRules) {
  solution::PasswordStrengthCalculator calculator;
  calculator.AddRules(GetParam().rules);
  VerifyScores(calculator, GetParam().expected_scores);
}

Rule MakeLengthRule(unsigned weight = Rule::kDefaultWeight) {
  return Rule{
      .verifier =
          [](std::string_view password) {
            constexpr unsigned kMinLength = 5;
            return password.length() >= kMinLength;
          },
      .weight = weight,
  };
}

Rule MakeStartsWithRule(unsigned weight = Rule::kDefaultWeight) {
  return Rule{
      .verifier =
          [](std::string_view password) {
            constexpr std::string_view kBeginning = "pa";
            return password.starts_with(kBeginning);
          },
      .weight = weight,
  };
}

Rule MakeContainsNumericDigitRule(unsigned weight = Rule::kDefaultWeight) {
  return Rule{
      .verifier =
          [](std::string_view password) {
            return std::ranges::any_of(password, [](const auto character) {
              return std::isdigit(character);
            });
          },
      .weight = weight,
  };
}

INSTANTIATE_TEST_SUITE_P(SameWeightSuite,
                         SameWeightFixture,
                         Values(
                             PasswordStrengthCalculatorTestData{
                                 .rules{},
                                 .expected_scores{
                                     {"password", 100},
                                 },
                             },
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(),
                                 },
                                 .expected_scores{
                                     {"pass", 0},
                                     {"passw", 100},
                                     {"password", 100},
                                 },
                             },
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(),
                                     MakeStartsWithRule(),
                                 },
                                 .expected_scores{
                                     {"word", 0},
                                     {"pass", 50},
                                     {"passw", 100},
                                     {"password", 100},
                                     {"wordpass", 50},
                                 },
                             },
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(),
                                     MakeStartsWithRule(),
                                     MakeContainsNumericDigitRule(),
                                 },
                                 .expected_scores{
                                     {"word", 0},
                                     {"wordpass", 33},
                                     {"pass", 33},
                                     {"wor1", 33},
                                     {"password", 66},
                                     {"wordpass1", 66},
                                     {"pa1", 66},
                                     {"password1", 100},
                                 },
                             }));

class MultipleWeightFixture : public PasswordStrengthCalculatorFixture {};

TEST_P(MultipleWeightFixture, RulesAddedInConstructor) {
  solution::PasswordStrengthCalculator calculator(GetParam().rules);
  VerifyScores(calculator, GetParam().expected_scores);
}

INSTANTIATE_TEST_SUITE_P(MultipleWeightSuite,
                         MultipleWeightFixture,
                         Values(
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(50),
                                 },
                                 .expected_scores{
                                     {"pass", 0},
                                     {"passw", 100},
                                     {"password", 100},
                                 },
                             },
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(1),
                                     MakeStartsWithRule(2),
                                 },
                                 .expected_scores{
                                     {"word", 0},
                                     {"pass", 66},
                                     {"passw", 100},
                                     {"password", 100},
                                     {"wordpass", 33},
                                 },
                             },
                             PasswordStrengthCalculatorTestData{
                                 .rules{
                                     MakeLengthRule(1),
                                     MakeStartsWithRule(2),
                                     MakeContainsNumericDigitRule(3),
                                 },
                                 .expected_scores{
                                     {"word", 0},
                                     {"wordpass", 16},
                                     {"pass", 33},
                                     {"wor1", 50},
                                     {"password", 50},
                                     {"wordpass1", 66},
                                     {"pa1", 83},
                                     {"password1", 100},
                                 },
                             }));

}  // namespace