#ifndef KERO_COMPILER_CORE_H
#define KERO_COMPILER_CORE_H

#include "cpp_tree_sitter/api.h"
#include "tree-sitter-kero.h"

auto Language() -> ts::Language {
  return ts::Language::FromRaw(tree_sitter_kero());
}

#endif // KERO_COMPILER_CORE_H