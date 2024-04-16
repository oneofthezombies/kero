#ifndef KERO_COMPILER_IR_VISITOR_H
#define KERO_COMPILER_IR_VISITOR_H

#include <functional>
#include <string_view>

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/Value.h"

#include "compiler/core.h"

namespace kero::compiler {

struct IrContext;

using IrVisitResult = Result<llvm::Value *, Error>;
using IrVisitHandler =
    std::function<IrVisitResult(IrContext &ir_context, const ts::Node &node)>;
using IrVisitHandlers = std::unordered_map<ts::Symbol, IrVisitHandler>;

class IrVisitor {
public:
  class Builder {
  public:
    explicit Builder() noexcept = default;
    Builder(const Builder &) = delete;
    Builder(Builder &&) = delete;
    ~Builder() noexcept = default;

    auto operator=(const Builder &) -> Builder & = delete;
    auto operator=(Builder &&) -> Builder & = delete;

    auto Build() noexcept -> Result<IrVisitor, Error>;

  private:
    auto RegisterAllHandler() noexcept -> VoidResult;
    auto RegisterHandler(const std::string_view type, const bool named,
                         const IrVisitHandler &handler) noexcept -> VoidResult;

    IrVisitHandlers handlers_;
  };

  IrVisitor(const IrVisitor &) = delete;
  IrVisitor(IrVisitor &&) noexcept = default;
  ~IrVisitor() noexcept = default;

  auto operator=(const IrVisitor &) -> IrVisitor & = delete;
  auto operator=(IrVisitor &&) noexcept -> IrVisitor & = default;

  auto Visit(IrContext &ir_context, const ts::Node &node) const noexcept
      -> IrVisitResult;

private:
  explicit IrVisitor(IrVisitHandlers &&handlers) noexcept;

  IrVisitHandlers handlers_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_IR_VISITOR_H
