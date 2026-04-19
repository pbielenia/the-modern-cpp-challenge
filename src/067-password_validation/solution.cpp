#include "solution.hpp"

#include <iterator>

namespace solution {

namespace {

constexpr unsigned kGreatestStrength = 100;

}

PasswordStrengthCalculator::PasswordStrengthCalculator(
    std::vector<Rule> new_rules)
    : rules_{std::move(new_rules)} {
  UpdateMaxScore();
}

void PasswordStrengthCalculator::UpdateMaxScore() {
  max_score_ = 0;
  for (const auto& rule : rules_) {
    max_score_ += rule.weight;
  }
}

void PasswordStrengthCalculator::AddRule(Rule rule) {
  rules_.push_back(std::move(rule));
  UpdateMaxScore();
}

void PasswordStrengthCalculator::AddRules(std::vector<Rule> new_rules) {
  rules_.reserve(rules_.size() + new_rules.size());
  rules_.insert(rules_.end(), std::make_move_iterator(new_rules.begin()),
                std::make_move_iterator(new_rules.end()));
  UpdateMaxScore();
}

unsigned PasswordStrengthCalculator::CalculatePasswordStrength(
    std::string_view password) const {
  if (rules_.empty()) {
    return kGreatestStrength;
  }

  unsigned score = 0;
  for (const auto& rule : rules_) {
    score += static_cast<unsigned>(rule.verifier(password)) * rule.weight;
  }
  return score * kGreatestStrength / max_score_;
}

}  // namespace solution
