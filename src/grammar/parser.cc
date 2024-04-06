#include "parser.h"

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/analyze.hpp>
#include <tao/pegtl/contrib/parse_tree.hpp>

namespace {

namespace _ = tao::pegtl;

struct Grammar : _::must<_::eof> {};

} // namespace

auto kero::grammar::Parser::analyze(const bool verbose) -> bool {
  const auto issues = _::analyze<Grammar>(verbose ? 1 : -1);
  return issues == 0;
}

auto kero::grammar::Parser::parse() -> bool {
  _::memory_input in("this is the input to parse", "");
  auto root = _::parse_tree::parse<Grammar>(in);
  return true;
}
