#include "parser_facade.h"

#include "parser/generated.h"

#include <cassert>
#include <iostream>

namespace {

enum class DebugEvent : int32_t {
  kRuleEvaluating = 0,
  kRuleMatched = 1,
  kRuleNotMatched = 2,
};

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

class ParserImpl : public ::KeroParserAuxil {
public:
  ParserImpl(const std::string_view source) noexcept : source_{source} {
    SetPccCallbacks();
    context_ = ::KeroParser_create(this);
  }

  ~ParserImpl() noexcept {
    ::KeroParser_destroy(context_);
    context_ = nullptr;
  }

  auto parse() noexcept -> bool {
    std::cout << "ParserImpl::parse() called" << std::endl;
    while (true) {
      ::KeroObject* ret{nullptr};
      if (::KeroParser_parse(context_, &ret) == 0) {
        break;
      }

      if (error_occurred_) {
        std::cout << "ParserImpl::parse() has error" << std::endl;
        break;
      }
    }

    return !error_occurred_;
  }

private:
  auto PccGetChar() noexcept -> int {
    if (source_position_ >= source_.size()) {
      return -1;
    }
    return source_[source_position_++];
  }

  auto PccError() noexcept -> void { error_occurred_ = true; }

  auto PccDebug(int event, const char* rule, size_t level, size_t pos,
                const char* buffer, size_t length) noexcept -> void {
    const DebugEvent debug_event{static_cast<DebugEvent>(event)};
    const std::string_view rule_view{rule};
    const std::string_view buffer_view{buffer, length};
    std::cout << "Parser::PccDebug() event " << debug_event << " rule "
              << rule_view << " level " << level << " pos " << pos
              << "buffer
                 "
              << buffer_view << std::endl;
  }

  auto SetPccCallbacks() noexcept -> void {
    pcc_get_char = &ParserImpl::PccGetChar;
    pcc_error = &ParserImpl::PccError;
    pcc_debug = &ParserImpl::PccDebug;
  }

  static auto PccGetChar(::KeroGrammarParserAuxil* auxil) -> int {
    return FromAuxil(auxil).PccGetChar();
  }

  static auto PccError(::KeroGrammarParserAuxil* auxil) -> void {
    FromAuxil(auxil).PccError();
  }

  static auto PccDebug(::KeroGrammarParserAuxil* auxil, int event,
                       const char* rule, size_t level, size_t pos,
                       const char* buffer, size_t length) -> void {
    FromAuxil(auxil).PccDebug(event, rule, level, pos, buffer, length);
  }

  static auto FromAuxil(::KeroGrammarParserAuxil* auxil) -> ParserImpl& {
    assert(auxil != nullptr);
    return *static_cast<ParserImpl*>(auxil);
  }

  std::string_view source_;
  size_t source_position_{0};
  ::KeroGrammarParser_context_t* context_{nullptr};
  bool error_occurred_{false};
};
} // namespace

ParserFacade::ParserFacade(const std::string_view source) noexcept
    : impl_(std::make_unique<ParserImpl>(source)) {}

auto ParserFacade::Parse() noexcept -> bool { return impl_->Parse(); }
