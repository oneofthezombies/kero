#ifndef KERO_COMPILER_IR_VISITOR_H
#define KERO_COMPILER_IR_VISITOR_H

#include <functional>
#include <string_view>

#include "cpp_tree_sitter/api.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

#include "compiler/core.h"

namespace kero::compiler {

class IrVisitor;

using LlvmContext = std::unique_ptr<llvm::LLVMContext>;
using LlvmModule = std::unique_ptr<llvm::Module>;
using LlvmIrBuilder = std::unique_ptr<llvm::IRBuilder<>>;

struct IrVisitorContext : public NonCopyAndNonMovable {
  const IrVisitor &ir_visitor;
  const LlvmContext &llvm_context;
  const LlvmModule &module;
  const LlvmIrBuilder &ir_builder;
  const std::string_view source;

  explicit IrVisitorContext(const IrVisitor &ir_visitor,
                            const LlvmContext &llvm_context,
                            const LlvmModule &module,
                            const LlvmIrBuilder &ir_builder,
                            const std::string_view source) noexcept;
};

using IrVisitResult = Result<llvm::Value *, Error>;
using IrVisitHandler = std::function<IrVisitResult(
    const IrVisitorContext &context, const ts::Node &node)>;
using IrVisitHandlers = std::unordered_map<ts::Symbol, IrVisitHandler>;

class IrVisitor : public NonCopyAndMovable {
public:
  class Builder : public NonCopyAndNonMovable {
  public:
    auto Build() noexcept -> Result<IrVisitor, Error>;

  private:
    auto RegisterAllHandler() noexcept -> VoidResult;
    auto RegisterHandler(const std::string_view type, const bool named,
                         const IrVisitHandler &handler) noexcept -> VoidResult;

    IrVisitHandlers handlers_;
  };

  auto Visit(const IrVisitorContext &context,
             const ts::Node &node) const noexcept -> IrVisitResult;

private:
  explicit IrVisitor(IrVisitHandlers &&handlers) noexcept;

  IrVisitHandlers handlers_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_IR_VISITOR_H
