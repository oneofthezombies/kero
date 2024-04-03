#include "./parser.h"

#include <iostream>

#include "./core.h"

namespace kero {
namespace grammar {

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

auto Parser::Parse() noexcept -> void {
  std::cout << "Parser::parse() called" << std::endl;
  int ret{0};
  while (true) {
    if (::KeroGrammarCore_parse(core_context_, &ret) == 0) {
      break;
    }

    if (error_occurred_) {
      std::cout << "Parser::parse() ret " << ret << std::endl;
      std::cout << "Parser::parse() has error" << std::endl;
      break;
    }
  }

  std::cout << "Parser::parse() returned " << ret << std::endl;
}

} // namespace grammar
} // namespace kero
