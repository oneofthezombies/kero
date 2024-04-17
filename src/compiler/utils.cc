#include "utils.h"

#include <cassert>
#include <sstream>

#include "tree-sitter-kero.h"

using namespace kero::compiler;

auto kero::compiler::Language() -> ts::Language {
  return ts::Language::FromRaw(tree_sitter_kero());
}

kero::compiler::NodeExt::NodeExt(const std::string_view source,
                                 const ts::Node &node) noexcept
    : ts::Node{node}, source_{source} {}

auto kero::compiler::NodeExt::ChildExt(const uint32_t index) const noexcept
    -> NodeExt {
  return NodeExt{source_, Child(index)};
}

auto kero::compiler::NodeExt::DebugString() const noexcept -> std::string {
  std::ostringstream oss;
  oss << AsRaw();
  return oss.str();
}

auto kero::compiler::NodeExt::Token() const noexcept -> std::string_view {
  const auto start = StartByte();
  assert(start >= 0 && "start byte must be greater than or equal to 0");
  assert(start < source_.size() && "start byte must be less than source size");

  const auto end = EndByte();
  assert(end >= 0 && "end byte must be greater than or equal to 0");
  assert(end <= source_.size() &&
         "end byte must be less than or equal to source size");

  const auto length = end - start;
  assert(length >= 0 && "length must be greater than or equal to 0");
  assert(length <= source_.size() &&
         "length must be less than or equal to source size");

  return source_.substr(start, length);
}

auto kero::compiler::NodeExt::AsRaw() const noexcept -> const ts::Node & {
  return *this;
}
