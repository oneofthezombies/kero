#include "compiler/parser.h"

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

// Parser::Builder
// --------

auto Parser::Builder::build() const noexcept -> std::optional<Parser> {
  auto parser = kero::ts::Parser{};
  if (!parser.set_language(tree_sitter_kero())) {
    return std::nullopt;
  }
  return Parser{std::move(parser)};
}

// Parser
// --------

Parser::Parser(kero::ts::Parser &&parser) noexcept
    : parser_{std::move(parser)} {}

auto Parser::parse(const std::string_view source) const noexcept
    -> std::optional<kero::ts::Tree> {
  return parser_.parse_string(kero::ts::Tree::null(), source);
}
