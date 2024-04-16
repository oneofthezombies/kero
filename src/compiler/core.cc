#include "core.h"

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

using namespace kero::compiler;

auto kero::compiler::Language() -> ts::Language {
  return ts::Language::FromRaw(tree_sitter_kero());
}
