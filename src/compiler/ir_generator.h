#ifndef KERO_COMPILER_IR_GENERATOR_H
#define KERO_COMPILER_IR_GENERATOR_H

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "compiler/ir_visitor.h"

namespace kero::compiler {

struct IrContext {
  const IrVisitor &ir_visitor;
  std::unique_ptr<llvm::LLVMContext> llvm_context;
  std::unique_ptr<llvm::Module> module;
  std::unique_ptr<llvm::IRBuilder<>> builder;

  explicit IrContext(const IrVisitor &ir_visitor) noexcept;
  IrContext(const IrContext &) = delete;
  IrContext(IrContext &&) = delete;
  ~IrContext() noexcept = default;

  auto operator=(const IrContext &) -> IrContext & = delete;
  auto operator=(IrContext &&) -> IrContext & = delete;
};

class IrGenerator {
public:
  explicit IrGenerator(const IrVisitor &ir_visitor) noexcept;
  IrGenerator(const IrGenerator &) = delete;
  IrGenerator(IrGenerator &&) = delete;
  ~IrGenerator() noexcept = default;

  auto operator=(const IrGenerator &) -> IrGenerator & = delete;
  auto operator=(IrGenerator &&) -> IrGenerator & = delete;

  auto Generate(ts::Tree &&tree) noexcept -> IrVisitResult;

private:
  IrContext ir_context_;
};

} // namespace kero::compiler

#endif // KERO_COMPILER_IR_GENERATOR_H
