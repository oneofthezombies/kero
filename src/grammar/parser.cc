#include "parser.h"

#include <memory>

#include "./c/gen/parser.h"
#include "./c/parser_auxil.h"

namespace kero {
namespace grammar {

Parser::Parser() noexcept
    : auxil_{std::make_unique<::KeroGrammarParserAuxilTag>()},
      context_{::KeroGrammarParser_create(auxil_.get())} {}

Parser::~Parser() noexcept { ::KeroGrammarParser_destroy(context_); }

auto Parser::parse() noexcept -> void {
  int ret{0};
  ::KeroGrammarParser_parse(context_, &ret);
}

} // namespace grammar
} // namespace kero
