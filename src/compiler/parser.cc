#include "compiler/parser.h"

#include "tree-sitter-kero.h"
#include "tree_sitter/api.h"

using namespace kero::compiler;

kero::compiler::Parser::Parser(const std::string_view source) noexcept
    : source_{source} {
  auto language = tree_sitter_kero();
}
