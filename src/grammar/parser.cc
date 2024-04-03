#include "./parser.h"

#include <iostream>

#include "./core.h"

namespace kero {
namespace grammar {

auto operator<<(std::ostream& os, const DebugEvent event) noexcept
    -> std::ostream& {
  switch (event) {
  case DebugEvent::kRuleEvaluating:
    os << "RuleEvaluating";
    break;
  case DebugEvent::kRuleMatched:
    os << "RuleMatched";
    break;
  case DebugEvent::kRuleNotMatched:
    os << "RuleNotMatched";
    break;
  }
  return os;
}

Parser::Parser(const std::string_view source) noexcept
    : source_{source}, core_context_{::KeroGrammarCore_create(this)} {}

Parser::~Parser() noexcept { ::KeroGrammarCore_destroy(core_context_); }

auto Parser::OnGetChar() noexcept -> int {
  if (source_index_ >= source_.size()) {
    return -1;
  }
  return source_[source_index_++];
}

auto Parser::OnError() noexcept -> void { error_occurred_ = true; }

auto Parser::OnDebug(int event, const char* rule, size_t level, size_t pos,
                     const char* buffer, size_t length) noexcept -> void {
  const DebugEvent debug_event{static_cast<DebugEvent>(event)};
  const std::string_view rule_view{rule};
  const std::string_view buffer_view{buffer, length};
  std::cout << "Parser::OnDebug() event " << debug_event << " rule "
            << rule_view << " level " << level << " pos " << pos << " buffer "
            << buffer_view << std::endl;
}

auto Parser::OnCreateNode() noexcept -> void* {
  std::cout << "Parser::OnCreateNode() called" << std::endl;
  return nullptr;
}

auto Parser::Parse() noexcept -> bool {
  std::cout << "Parser::parse() called" << std::endl;
  while (true) {
    void* ret{nullptr};
    if (::KeroGrammarCore_parse(core_context_, &ret) == 0) {
      break;
    }

    if (error_occurred_) {
      std::cout << "Parser::parse() has error" << std::endl;
      break;
    }
  }

  return !error_occurred_;
}

} // namespace grammar
} // namespace kero
