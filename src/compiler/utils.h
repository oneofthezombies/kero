#ifndef KERO_COMPILER_UTILS_H
#define KERO_COMPILER_UTILS_H

#include <string>

#include "cpp_tree_sitter/api.h"

#include "compiler/core.h"

namespace kero::compiler {

auto Language() -> ts::Language;

class NodeExt final : public ts::Node, private Copyable, Movable {
public:
  NodeExt(const std::string_view source, const ts::Node &node) noexcept;

  [[nodiscard]] auto ChildExt(const uint32_t index) const noexcept -> NodeExt;

  [[nodiscard]] auto DebugString() const noexcept -> std::string;

  auto Token() const noexcept -> std::string_view;

  auto AsRaw() const noexcept -> const ts::Node &;

private:
  const std::string_view source_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_UTILS_H
