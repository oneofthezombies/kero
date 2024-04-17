#include "utils.h"

#include <sstream>

#include "tree-sitter-kero.h"

using namespace kero::compiler;

auto kero::compiler::Language() -> ts::Language {
  return ts::Language::FromRaw(tree_sitter_kero());
}

auto kero::compiler::NodeToString(const ts::Node &node) noexcept
    -> std::string {
  std::stringstream ss;
  ss << node;
  return ss.str();
}
