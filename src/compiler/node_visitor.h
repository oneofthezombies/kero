#ifndef KERO_COMPILER_NODE_VISITOR_H
#define KERO_COMPILER_NODE_VISITOR_H

#include <functional>
#include <string_view>

#include "compiler/core.h"

namespace kero::compiler {

using VisitHandler =
    std::function<Result<ValueRef>(Context &context, const ts::Node &node)>;

class NodeVisitor {
public:
  class Builder {
  public:
    Builder() noexcept;
    Builder(const Builder &) = delete;
    Builder(Builder &&) noexcept = default;
    ~Builder() noexcept = default;

    auto operator=(const Builder &) -> Builder & = delete;
    auto operator=(Builder &&) noexcept -> Builder & = default;

    auto Build() noexcept -> Result<NodeVisitor>;
  };

  NodeVisitor(const NodeVisitor &) = delete;
  NodeVisitor(NodeVisitor &&) noexcept = default;
  ~NodeVisitor() noexcept = default;

  auto operator=(const NodeVisitor &) -> NodeVisitor & = delete;
  auto operator=(NodeVisitor &&) noexcept -> NodeVisitor & = default;

private:
  explicit NodeVisitor() noexcept = default;

  auto RegisterAllHandler() noexcept -> ResultCode;
  auto RegisterHandler(const std::string_view type, const bool named,
                       const VisitHandler &handler) noexcept -> ResultCode;

  std::unordered_map<ts::Symbol, VisitHandler> handlers_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_NODE_VISITOR_H