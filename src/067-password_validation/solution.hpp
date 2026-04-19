#pragma once

#include <functional>
#include <string_view>
#include <vector>

namespace solution {

class PasswordStrengthCalculator {
 public:
  struct Rule {
    // Validates whether a password satisfies this rule. Returns true if the
    // rule passes.
    using Verifier = std::function<bool(std::string_view)>;

    static constexpr unsigned kDefaultWeight = 10;

    Verifier verifier;
    unsigned weight = kDefaultWeight;
  };

  PasswordStrengthCalculator() = default;
  // Constructs the calculator with an initial rule set.
  explicit PasswordStrengthCalculator(std::vector<Rule> new_rules);

  // Adds a single validation rule.
  void AddRule(Rule rule);

  // Adds multiple validation rules.
  void AddRules(std::vector<Rule> new_rules);

  // Calculates strength based on configured rules.
  // Score is normalized to [0, 100].
  unsigned CalculatePasswordStrength(std::string_view password) const;

 private:
  // Recalculates the maximum achievable score from the current rules.
  void UpdateMaxScore();

  std::vector<Rule> rules_;
  unsigned max_score_ = 0;  // Sum of all rule weights
};

}  // namespace solution